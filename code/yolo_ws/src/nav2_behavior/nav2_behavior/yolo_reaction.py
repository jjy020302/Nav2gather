import rclpy
from geometry_msgs.msg import TwistStamped
from rclpy.node import Node
from yolo_msgs.msg import DetectionArray


class YoloReaction(Node):
    """
    YOLO로 bottle을 찾을 때까지 TurtleBot3를 제자리 회전시키고,
    bottle이 검출되면 화면 중앙에 오도록 좌우 정렬하는 노드.
    """

    def __init__(self):
        super().__init__('yolo_reaction')

        # ---------------------------------------------------------
        # 사용자 설정값
        # ---------------------------------------------------------

        # 인식할 물체
        self.target_class = 'bottle'

        # 카메라 영상 크기: 현재 640x480
        self.image_width = 640.0

        # 화면 중앙으로 판단할 범위
        self.center_min = 260.0
        self.center_max = 380.0

        # 최소 검출 신뢰도
        self.score_threshold = 0.7

        # 회전 속도
        self.angular_speed = 0.25

        # 검출 메시지가 일정 시간 없을 때 탐색 회전 시작
        self.detection_timeout = 0.5

        # ---------------------------------------------------------
        # Publisher / Subscriber
        # ---------------------------------------------------------

        # 현재 TurtleBot3의 /cmd_vel 타입은 TwistStamped
        self.cmd_vel_pub = self.create_publisher(
            TwistStamped,
            '/cmd_vel',
            10
        )

        self.detection_sub = self.create_subscription(
            DetectionArray,
            '/yolo/detections',
            self.detection_callback,
            10
        )

        # 마지막 검출 메시지 수신 시간
        self.last_detection_time = self.get_clock().now()

        # YOLO 메시지가 끊겨도 탐색 회전을 계속하기 위한 타이머
        self.search_timer = self.create_timer(
            0.2,
            self.check_detection_timeout
        )

        self.get_logger().info(
            f"YOLO Reaction 시작: 대상='{self.target_class}', "
            f"회전 속도={self.angular_speed:.2f} rad/s"
        )

        self.get_logger().info(
            f"'{self.target_class}' 미검출 시 탐색 회전을 시작합니다."
        )

    def create_cmd(self, angular_z=0.0):
        """
        현재 시간 정보가 포함된 TwistStamped 명령을 생성한다.
        """

        cmd = TwistStamped()

        cmd.header.stamp = self.get_clock().now().to_msg()
        cmd.header.frame_id = ''

        cmd.twist.linear.x = 0.0
        cmd.twist.linear.y = 0.0
        cmd.twist.linear.z = 0.0

        cmd.twist.angular.x = 0.0
        cmd.twist.angular.y = 0.0
        cmd.twist.angular.z = float(angular_z)

        return cmd

    def detection_callback(self, msg):
        """
        YOLO 검출 결과를 받아 bottle 위치에 따라 회전 방향을 결정한다.
        """

        # YOLO 메시지를 받았으므로 수신 시간을 갱신
        self.last_detection_time = self.get_clock().now()

        target = None

        # 조건을 만족하는 bottle 중 신뢰도가 가장 높은 것을 선택
        for detection in msg.detections:
            if (
                detection.class_name == self.target_class
                and detection.score >= self.score_threshold
            ):
                if target is None or detection.score > target.score:
                    target = detection

        # bottle이 검출되지 않으면 한 방향으로 계속 탐색 회전
        if target is None:
            self.publish_rotation(self.angular_speed)

            self.get_logger().info(
                f'{self.target_class} 미검출 → 탐색 회전',
                throttle_duration_sec=1.0
            )

            return

        # 검출된 bottle의 화면 가로 중심 위치
        center_x = target.bbox.center.position.x

        # bottle이 화면 왼쪽에 있을 때
        if center_x < self.center_min:
            self.publish_rotation(self.angular_speed)

            self.get_logger().info(
                f'{self.target_class} 왼쪽 검출: '
                f'x={center_x:.1f}, score={target.score:.2f} '
                f'→ 왼쪽 회전',
                throttle_duration_sec=1.0
            )

        # bottle이 화면 오른쪽에 있을 때
        elif center_x > self.center_max:
            self.publish_rotation(-self.angular_speed)

            self.get_logger().info(
                f'{self.target_class} 오른쪽 검출: '
                f'x={center_x:.1f}, score={target.score:.2f} '
                f'→ 오른쪽 회전',
                throttle_duration_sec=1.0
            )

        # bottle이 화면 중앙에 들어온 경우
        else:
            self.publish_stop()

            self.get_logger().info(
                f'{self.target_class} 중앙 정렬 완료: '
                f'x={center_x:.1f}, score={target.score:.2f} '
                f'→ 정지',
                throttle_duration_sec=1.0
            )

    def check_detection_timeout(self):
        """
        /yolo/detections 메시지가 일정 시간 들어오지 않아도
        로봇이 멈추지 않고 bottle 탐색 회전을 계속하도록 한다.
        """

        elapsed = (
            self.get_clock().now() - self.last_detection_time
        ).nanoseconds / 1e9

        if elapsed > self.detection_timeout:
            self.publish_rotation(self.angular_speed)

            self.get_logger().warn(
                '/yolo/detections 메시지 없음 '
                f'({elapsed:.1f}초) → 탐색 회전',
                throttle_duration_sec=2.0
            )

    def publish_rotation(self, angular_z):
        """
        지정한 각속도로 제자리 회전 명령을 발행한다.
        """

        cmd = self.create_cmd(angular_z)
        self.cmd_vel_pub.publish(cmd)

    def publish_stop(self):
        """
        정지 명령을 발행한다.
        """

        stop_cmd = self.create_cmd(0.0)
        self.cmd_vel_pub.publish(stop_cmd)

    def destroy_node(self):
        """
        노드 종료 시 로봇을 정지시킨다.
        """

        self.publish_stop()
        super().destroy_node()


def main(args=None):
    rclpy.init(args=args)

    node = YoloReaction()

    try:
        rclpy.spin(node)

    except KeyboardInterrupt:
        node.get_logger().info(
            'YOLO Reaction 노드를 종료합니다.'
        )

    finally:
        node.publish_stop()
        node.destroy_node()

        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()


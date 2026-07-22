#!/usr/bin/env python3

import rclpy
from geometry_msgs.msg import Twist
from rclpy.node import Node
from yolo_msgs.msg import DetectionArray


class YoloReaction(Node):
    """YOLO 검출 위치에 따라 TurtleBot3를 좌우로 회전시키는 노드."""

    def __init__(self):
        super().__init__('yolo_reaction')

        # 인식할 물체
        self.target_class = 'bottle'

        # 카메라 영상 가로 크기: 현재 설정 640x480
        self.image_width = 640.0

        # 화면 중앙으로 판단할 범위
        self.center_min = 260.0
        self.center_max = 380.0

        # 최소 검출 신뢰도
        self.score_threshold = 0.7

        # 회전 속도
        self.angular_speed = 0.25

        self.cmd_vel_pub = self.create_publisher(
            Twist,
            '/cmd_vel',
            10
        )

        self.detection_sub = self.create_subscription(
            DetectionArray,
            '/yolo/detections',
            self.detection_callback,
            10
        )

        # 검출 메시지가 끊겼을 때 정지시키기 위한 타이머
        self.last_detection_time = self.get_clock().now()
        self.stop_timer = self.create_timer(
            0.2,
            self.check_detection_timeout
        )

        self.get_logger().info(
            f"'{self.target_class}' 검출을 기다립니다."
        )

    def detection_callback(self, msg):
        target = None

        # 조건을 만족하는 검출 중 신뢰도가 가장 높은 것을 선택
        for detection in msg.detections:
            if (
                detection.class_name == self.target_class
                and detection.score >= self.score_threshold
            ):
                if target is None or detection.score > target.score:
                    target = detection

        if target is None:
            self.publish_stop()
            return

        self.last_detection_time = self.get_clock().now()

        center_x = target.bbox.center.position.x

        cmd = Twist()

        if center_x < self.center_min:
            # 영상에서 물체가 왼쪽에 있으므로 왼쪽 회전
            cmd.angular.z = self.angular_speed

            self.get_logger().info(
                f'{self.target_class} 왼쪽 검출: '
                f'x={center_x:.1f} → 왼쪽 회전',
                throttle_duration_sec=1.0
            )

        elif center_x > self.center_max:
            # 영상에서 물체가 오른쪽에 있으므로 오른쪽 회전
            cmd.angular.z = -self.angular_speed

            self.get_logger().info(
                f'{self.target_class} 오른쪽 검출: '
                f'x={center_x:.1f} → 오른쪽 회전',
                throttle_duration_sec=1.0
            )

        else:
            # 화면 중앙에 들어오면 정지
            cmd.angular.z = 0.0

            self.get_logger().info(
                f'{self.target_class} 중앙 정렬 완료: '
                f'x={center_x:.1f} → 정지',
                throttle_duration_sec=1.0
            )

        self.cmd_vel_pub.publish(cmd)

    def check_detection_timeout(self):
        elapsed = (
            self.get_clock().now() - self.last_detection_time
        ).nanoseconds / 1e9

        if elapsed > 0.5:
            self.publish_stop()

    def publish_stop(self):
        stop_cmd = Twist()
        self.cmd_vel_pub.publish(stop_cmd)

    def destroy_node(self):
        # 종료할 때 반드시 정지 명령 발행
        self.publish_stop()
        super().destroy_node()


def main(args=None):
    rclpy.init(args=args)

    node = YoloReaction()

    try:
        rclpy.spin(node)

    except KeyboardInterrupt:
        node.get_logger().info('YOLO 반응 노드를 종료합니다.')

    finally:
        node.publish_stop()
        node.destroy_node()

        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()

#!/usr/bin/env python3

import time
from typing import Optional, Tuple

import rclpy
from geometry_msgs.msg import Twist
from rclpy.node import Node
from yolo_msgs.msg import DetectionArray


class BottleFollower(Node):
    """
    Bottle 탐색 및 접근 노드.

    동작:
    1. Bottle이 보이지 않으면 제자리 회전
    2. Bottle이 보이면 화면 중앙으로 정렬
    3. 중앙에 정렬되면 전진
    4. Bounding box가 일정 크기 이상이면 정지
    """

    def __init__(self) -> None:
        super().__init__('bottle_follower_node')

        # =========================================================
        # 설정값
        # =========================================================

        self.target_class = 'bottle'

        # YOLO 최소 신뢰도
        self.minimum_score = 0.50

        # 카메라 해상도
        self.image_width = 640.0
        self.image_center_x = self.image_width / 2.0

        # 화면 중앙 오차 허용 범위
        # 0.12 = 화면 중심 기준 좌우 약 12%
        self.center_tolerance = 0.12

        # 안전거리 판정용 Bounding box 면적
        #
        # 이전 로그에서 물병 면적이 약 43,000이었으므로
        # 그보다 조금 가까이 접근하도록 55,000으로 설정
        self.stop_bbox_area = 55000.0

        # 안전거리 조건을 연속으로 만족해야 하는 횟수
        self.required_stop_count = 3

        # 물병을 찾을 때 회전 속도
        self.search_angular_speed = 0.18

        # 물병 방향으로 정렬할 때 최대 회전 속도
        self.maximum_tracking_angular_speed = 0.25

        # 방향 보정 비례 게인
        self.angular_gain = 0.45

        # 물병을 향해 접근할 때 전진 속도
        self.approach_linear_speed = 0.05

        # YOLO 메시지가 이 시간 이상 안 들어오면 물병을 놓친 것으로 판단
        self.target_timeout = 0.6

        # =========================================================
        # 상태 변수
        # =========================================================

        self.target_visible = False
        self.target_center_x = self.image_center_x
        self.target_area = 0.0
        self.target_score = 0.0

        self.last_detection_time = 0.0
        self.stop_count = 0
        self.stopped = False

        self.last_state = ''

        # =========================================================
        # ROS Publisher / Subscriber
        # =========================================================

        self.cmd_vel_publisher = self.create_publisher(
            Twist,
            '/cmd_vel',
            10,
        )

        self.detection_subscription = self.create_subscription(
            DetectionArray,
            '/yolo/detections',
            self.detection_callback,
            10,
        )

        # 10 Hz 제어 주기
        self.control_timer = self.create_timer(
            0.1,
            self.control_callback,
        )

        self.get_logger().info('Bottle follower started.')
        self.get_logger().info(
            'SEARCH -> ALIGN -> APPROACH -> STOP'
        )
        self.get_logger().info(
            f'target={self.target_class}, '
            f'score>={self.minimum_score:.2f}, '
            f'stop area>={self.stop_bbox_area:.0f}'
        )
        self.get_logger().warn(
            'Robot will rotate and move automatically. '
            'Keep the test area clear.'
        )

    def get_bbox_values(
        self,
        detection,
    ) -> Optional[Tuple[float, float, float]]:
        """
        Bounding box 중심 x, 폭, 높이를 읽는다.

        yolo_msgs 또는 vision_msgs 버전에 따라
        center 표현이 다를 가능성에 대응한다.
        """

        try:
            width = float(detection.bbox.size.x)
            height = float(detection.bbox.size.y)

            if hasattr(detection.bbox.center, 'position'):
                center_x = float(
                    detection.bbox.center.position.x
                )
            else:
                center_x = float(
                    detection.bbox.center.x
                )

            return center_x, width, height

        except (AttributeError, TypeError, ValueError) as error:
            self.get_logger().error(
                f'Unable to read bounding box: {error}'
            )
            return None

    def detection_callback(
        self,
        msg: DetectionArray,
    ) -> None:
        """검출된 bottle 중 가장 큰 객체를 추적 대상으로 선택한다."""

        if self.stopped:
            return

        selected_target = None
        selected_area = 0.0
        selected_score = 0.0

        for detection in msg.detections:
            class_name = detection.class_name.lower()

            if class_name != self.target_class:
                continue

            score = float(detection.score)

            if score < self.minimum_score:
                continue

            bbox_values = self.get_bbox_values(detection)

            if bbox_values is None:
                continue

            center_x, width, height = bbox_values
            area = width * height

            # 여러 bottle이 있으면 화면에서 가장 크게 보이는 bottle 선택
            if area > selected_area:
                selected_target = center_x
                selected_area = area
                selected_score = score

        if selected_target is None:
            self.target_visible = False
            self.stop_count = 0
            return

        self.target_visible = True
        self.target_center_x = selected_target
        self.target_area = selected_area
        self.target_score = selected_score
        self.last_detection_time = time.monotonic()

        normalized_error = (
            self.target_center_x - self.image_center_x
        ) / self.image_center_x

        self.get_logger().info(
            f'Bottle: score={self.target_score:.2f}, '
            f'center_x={self.target_center_x:.1f}, '
            f'error={normalized_error:.2f}, '
            f'area={self.target_area:.1f}'
        )

        # 안전거리 조건을 연속으로 확인
        if self.target_area >= self.stop_bbox_area:
            self.stop_count += 1
        else:
            self.stop_count = 0

        if self.stop_count >= self.required_stop_count:
            self.stopped = True
            self.publish_stop()
            self.print_state(
                'STOP',
                'Bottle entered the safety distance.',
            )

    def control_callback(self) -> None:
        """현재 검출 상태에 따라 회전, 정렬, 접근 또는 정지한다."""

        if self.stopped:
            self.publish_stop()
            return

        current_time = time.monotonic()

        detection_is_recent = (
            self.target_visible
            and
            current_time - self.last_detection_time
            <= self.target_timeout
        )

        # =========================================================
        # 1. Bottle이 보이지 않으면 제자리 회전
        # =========================================================

        if not detection_is_recent:
            self.target_visible = False
            self.stop_count = 0

            command = Twist()
            command.linear.x = 0.0
            command.angular.z = self.search_angular_speed

            self.cmd_vel_publisher.publish(command)

            self.print_state(
                'SEARCH',
                'Bottle not visible. Rotating to search.',
            )
            return

        normalized_error = (
            self.target_center_x - self.image_center_x
        ) / self.image_center_x

        # =========================================================
        # 2. 안전거리 안이면 정지
        # =========================================================

        if self.target_area >= self.stop_bbox_area:
            self.publish_stop()

            self.print_state(
                'WAIT_STOP',
                (
                    f'Safety-distance check '
                    f'{self.stop_count}/{self.required_stop_count}'
                ),
            )
            return

        # =========================================================
        # 3. Bottle이 화면 중앙에서 벗어났으면 방향 정렬
        # =========================================================

        if abs(normalized_error) > self.center_tolerance:
            angular_speed = (
                -self.angular_gain * normalized_error
            )

            angular_speed = max(
                -self.maximum_tracking_angular_speed,
                min(
                    self.maximum_tracking_angular_speed,
                    angular_speed,
                ),
            )

            command = Twist()
            command.linear.x = 0.0
            command.angular.z = angular_speed

            self.cmd_vel_publisher.publish(command)

            direction = (
                'right'
                if normalized_error > 0.0
                else 'left'
            )

            self.print_state(
                'ALIGN',
                f'Turning {direction} toward bottle.',
            )
            return

        # =========================================================
        # 4. Bottle이 중앙에 있으면 앞으로 접근
        # =========================================================

        angular_speed = (
            -self.angular_gain * normalized_error
        )

        command = Twist()
        command.linear.x = self.approach_linear_speed
        command.angular.z = angular_speed

        self.cmd_vel_publisher.publish(command)

        self.print_state(
            'APPROACH',
            (
                f'Moving toward bottle. '
                f'area={self.target_area:.0f}/'
                f'{self.stop_bbox_area:.0f}'
            ),
        )

    def print_state(
        self,
        state: str,
        message: str,
    ) -> None:
        """상태가 바뀔 때만 로그를 출력한다."""

        if state == self.last_state:
            return

        self.last_state = state
        self.get_logger().info(
            f'[{state}] {message}'
        )

    def publish_stop(self) -> None:
        """속도 0 명령을 발행한다."""

        stop_command = Twist()
        stop_command.linear.x = 0.0
        stop_command.angular.z = 0.0

        self.cmd_vel_publisher.publish(stop_command)

    def destroy_node(self) -> bool:
        """종료 전에 정지 명령을 여러 번 발행한다."""

        for _ in range(5):
            self.publish_stop()

        return super().destroy_node()


def main(args=None) -> None:
    rclpy.init(args=args)

    node = BottleFollower()

    try:
        rclpy.spin(node)

    except KeyboardInterrupt:
        node.get_logger().info(
            'Bottle follower stopped by user.'
        )

    finally:
        node.publish_stop()
        node.destroy_node()

        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()

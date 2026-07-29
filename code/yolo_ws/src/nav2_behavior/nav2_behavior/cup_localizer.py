#!/usr/bin/env python3

import math

import rclpy
from geometry_msgs.msg import PointStamped
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from yolo_msgs.msg import DetectionArray


class CupLocalizer(Node):
    """
    YOLO의 bottle bounding box를 이용해
    bottle의 camera_optical_frame 좌표를 추정하는 노드.
    """

    def __init__(self):
        super().__init__('cup_localizer')

        # ---------------------------------------------------------
        # 사용자 설정값
        # ---------------------------------------------------------

        self.target_class = 'bottle'

        self.image_width = 640.0
        self.image_height = 480.0

        # Logitech C920 기준 수평 화각
        self.horizontal_fov_deg = 78.0

        # 낮은 신뢰도 검출 제거
        self.score_threshold = 0.30

        # 실제 bottle의 대략적인 폭
        self.object_width_m = 0.065

        # 거리 보정 계수
        # 처음에는 1.0으로 실행하고 실제 거리와 비교해 조정
        self.distance_scale = 1.0

        # 비정상 거리 제거
        self.minimum_distance = 0.20
        self.maximum_distance = 4.00

        # ---------------------------------------------------------
        # 카메라 초점거리 계산
        # ---------------------------------------------------------

        horizontal_fov_rad = math.radians(
            self.horizontal_fov_deg
        )

        self.focal_length_px = (
            self.image_width
            / (
                2.0
                * math.tan(horizontal_fov_rad / 2.0)
            )
        )

        # ---------------------------------------------------------
        # Publisher / Subscriber
        # ---------------------------------------------------------

        self.point_pub = self.create_publisher(
            PointStamped,
            '/bottle/point',
            10
        )

        self.detection_sub = self.create_subscription(
            DetectionArray,
            '/yolo/detections',
            self.detection_callback,
            qos_profile_sensor_data
        )

        self.get_logger().info(
            'Bottle Localizer 시작'
        )

        self.get_logger().info(
            f'대상={self.target_class}, '
            f'score threshold={self.score_threshold:.2f}, '
            f'HFOV={self.horizontal_fov_deg:.1f} deg'
        )

    def detection_callback(self, msg):
        """YOLO 검출 결과에서 bottle을 찾아 좌표를 발행한다."""

        candidates = []

        for detection in msg.detections:

            if detection.class_name != self.target_class:
                continue

            if detection.score < self.score_threshold:
                continue

            bbox_width = float(
                detection.bbox.size.x
            )

            if bbox_width <= 1.0:
                continue

            candidates.append(detection)

        if not candidates:
            return

        # 가장 신뢰도가 높은 bottle 선택
        target = max(
            candidates,
            key=lambda detection: detection.score
        )

        bbox_center_x = float(
            target.bbox.center.position.x
        )

        bbox_center_y = float(
            target.bbox.center.position.y
        )

        bbox_width = float(
            target.bbox.size.x
        )

        # 핀홀 카메라 모델을 이용한 거리 추정
        distance = (
            self.object_width_m
            * self.focal_length_px
            / bbox_width
        )

        distance *= self.distance_scale

        if not (
            self.minimum_distance
            <= distance
            <= self.maximum_distance
        ):
            self.get_logger().warn(
                f'bottle 거리 범위 초과: {distance:.2f} m',
                throttle_duration_sec=1.0
            )
            return

        # 영상 중심 기준 수평 각도
        horizontal_angle = math.atan2(
            bbox_center_x - self.image_width / 2.0,
            self.focal_length_px
        )

        # optical frame:
        # x = 오른쪽
        # y = 아래
        # z = 전방
        point = PointStamped()

        point.header = msg.header
        point.header.frame_id = 'camera_optical_frame'

        point.point.x = (
            distance * math.sin(horizontal_angle)
        )

        point.point.y = (
            (
                bbox_center_y
                - self.image_height / 2.0
            )
            * distance
            / self.focal_length_px
        )

        point.point.z = (
            distance * math.cos(horizontal_angle)
        )

        self.point_pub.publish(point)

        self.get_logger().info(
            f'bottle 검출: '
            f'score={target.score:.2f}, '
            f'bbox_width={bbox_width:.1f}px, '
            f'distance={distance:.2f}m, '
            f'point=({point.point.x:.2f}, '
            f'{point.point.y:.2f}, '
            f'{point.point.z:.2f})',
            throttle_duration_sec=0.5
        )


def main(args=None):
    rclpy.init(args=args)

    node = CupLocalizer()

    try:
        rclpy.spin(node)

    except KeyboardInterrupt:
        node.get_logger().info(
            'Bottle Localizer 종료'
        )

    finally:
        node.destroy_node()

        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()

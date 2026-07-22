#!/usr/bin/env python3

import math
import statistics
from typing import Optional

import rclpy
from rclpy.node import Node

from geometry_msgs.msg import PointStamped
from yolo_msgs.msg import DetectionArray


class CupLocalizer(Node):
    """
    YOLO 바운딩박스와 실제 컵 너비를 이용해 컵의 3차원 위치를 추정한다.

    좌표계:
      x: 카메라 기준 오른쪽
      y: 카메라 기준 아래쪽
      z: 카메라 기준 전방

    보정 방법:
      실제 너비가 8 cm인 컵을 카메라 정면 1 m 위치에 놓고
      YOLO 바운딩박스 너비를 여러 프레임 측정한다.
    """

    def __init__(self) -> None:
        super().__init__('cup_localizer')

        # --------------------------------------------------
        # 사용자 설정값
        # --------------------------------------------------
        self.target_class = 'cup'

        self.image_width = 640.0
        self.image_height = 480.0

        # 컵의 실제 너비: 8 cm
        self.cup_width_m = 0.08

        # 보정 시 컵과 카메라 사이 거리
        self.reference_distance_m = 1.0

        # True: 1 m 거리에서 바운딩박스 너비 보정
        # False: 저장된 reference_width_px로 거리 계산
        self.calibration_mode = False

        # calibration_mode=False로 변경한 후
        # 보정 로그에 나온 값을 여기에 입력한다.
        self.reference_width_px = 43.73

        # 보정에 사용할 검출 개수
        self.calibration_sample_count = 30

        # 너무 작거나 이상한 바운딩박스 제외
        self.minimum_bbox_width_px = 5.0

        # 검출 신뢰도 기준
        self.minimum_score = 0.50

        # --------------------------------------------------
        # 내부 변수
        # --------------------------------------------------
        self.calibration_widths: list[float] = []

        # 보정된 카메라 초점거리(pixel)
        self.fx_px: Optional[float] = None

        if not self.calibration_mode:
            self.fx_px = (
                self.reference_width_px
                * self.reference_distance_m
                / self.cup_width_m
            )

        self.detection_sub = self.create_subscription(
            DetectionArray,
            '/yolo/detections',
            self.detection_callback,
            10,
        )

        self.point_pub = self.create_publisher(
            PointStamped,
            '/cup/point_camera',
            10,
        )

        self.get_logger().info('Cup Localizer를 시작했습니다.')
        self.get_logger().info(
            f'대상={self.target_class}, '
            f'실제 컵 너비={self.cup_width_m * 100:.1f} cm'
        )

        if self.calibration_mode:
            self.get_logger().warn(
                '보정 모드입니다. 컵을 카메라 정면 1.00 m 위치에 놓으세요.'
            )
        else:
            self.get_logger().info(
                f'보정값={self.reference_width_px:.2f} px, '
                f'fx={self.fx_px:.2f} px'
            )

    def detection_callback(self, msg: DetectionArray) -> None:
        best_detection = None
        best_score = 0.0

        for detection in msg.detections:
            class_name = self.get_class_name(detection)
            score = self.get_score(detection)

            if class_name != self.target_class:
                continue

            if score < self.minimum_score:
                continue

            if score > best_score:
                best_score = score
                best_detection = detection

        if best_detection is None:
            return

        bbox = self.get_bbox(best_detection)

        if bbox is None:
            self.get_logger().warn(
                'YOLO Detection 메시지에서 bbox를 읽을 수 없습니다.',
                throttle_duration_sec=2.0,
            )
            return

        center_x, center_y, bbox_width, bbox_height = bbox

        if bbox_width < self.minimum_bbox_width_px:
            self.get_logger().warn(
                f'바운딩박스가 너무 작습니다: {bbox_width:.1f} px',
                throttle_duration_sec=2.0,
            )
            return

        if self.calibration_mode:
            self.process_calibration(bbox_width)
            return

        if self.fx_px is None:
            self.get_logger().error('초점거리 보정값이 없습니다.')
            return

        point = self.calculate_3d_point(
            center_x,
            center_y,
            bbox_width,
        )

        if point is None:
            return

        x, y, z = point

        point_msg = PointStamped()
        point_msg.header = msg.header

        # msg.header.frame_id가 비어 있으면 카메라 프레임을 직접 지정
        if not point_msg.header.frame_id:
            point_msg.header.frame_id = 'camera_optical_frame'

        point_msg.point.x = x
        point_msg.point.y = y
        point_msg.point.z = z

        self.point_pub.publish(point_msg)

        horizontal_distance = math.sqrt((x * x) + (z * z))

        self.get_logger().info(
            f'컵 3D 위치: '
            f'x={x:.2f} m, '
            f'y={y:.2f} m, '
            f'z={z:.2f} m, '
            f'평면거리={horizontal_distance:.2f} m, '
            f'bbox={bbox_width:.1f} px, '
            f'score={best_score:.2f}'
        )

    def process_calibration(self, bbox_width: float) -> None:
        """
        컵을 1 m 위치에 놓고 bbox 너비를 여러 번 측정한다.
        """
        self.calibration_widths.append(bbox_width)

        count = len(self.calibration_widths)

        self.get_logger().info(
            f'보정 측정 {count}/{self.calibration_sample_count}: '
            f'bbox_width={bbox_width:.1f} px'
        )

        if count < self.calibration_sample_count:
            return

        reference_width = statistics.median(
            self.calibration_widths
        )

        fx_px = (
            reference_width
            * self.reference_distance_m
            / self.cup_width_m
        )

        self.reference_width_px = reference_width
        self.fx_px = fx_px
        self.calibration_mode = False

        self.get_logger().warn(
            '컵 거리 보정이 완료되었습니다.'
        )

        self.get_logger().warn(
            f'reference_width_px={reference_width:.2f}'
        )

        self.get_logger().warn(
            f'계산된 fx={fx_px:.2f} px'
        )

        self.get_logger().warn(
            '다음 실행부터 코드의 reference_width_px에 '
            f'{reference_width:.2f}를 입력하고 '
            'calibration_mode=False로 변경하세요.'
        )

    def calculate_3d_point(
        self,
        center_x: float,
        center_y: float,
        bbox_width: float,
    ) -> Optional[tuple[float, float, float]]:
        """
        핀홀 카메라 모델을 이용해 카메라 좌표계의 3D 좌표를 계산한다.
        """
        if self.fx_px is None:
            return None

        # 실제 컵 너비와 영상 속 컵 너비로 깊이 계산
        z = (
            self.fx_px
            * self.cup_width_m
            / bbox_width
        )

        # 영상 중심점
        cx = self.image_width / 2.0
        cy = self.image_height / 2.0

        # 일반 웹캠은 fx와 fy가 비슷하다고 가정
        fy_px = self.fx_px

        # 카메라 optical frame 기준
        x = ((center_x - cx) * z) / self.fx_px
        y = ((center_y - cy) * z) / fy_px

        if not all(math.isfinite(v) for v in (x, y, z)):
            return None

        if z <= 0.0:
            return None

        return x, y, z

    @staticmethod
    def get_class_name(detection) -> str:
        """
        yolo_msgs 버전에 따라 class_name 또는 class_id를 읽는다.
        """
        if hasattr(detection, 'class_name'):
            return str(detection.class_name)

        if hasattr(detection, 'class_id'):
            return str(detection.class_id)

        return ''

    @staticmethod
    def get_score(detection) -> float:
        if hasattr(detection, 'score'):
            return float(detection.score)

        if hasattr(detection, 'confidence'):
            return float(detection.confidence)

        return 0.0

    @staticmethod
    def get_bbox(
        detection,
    ) -> Optional[tuple[float, float, float, float]]:
        """
        yolo_msgs BoundingBox2D 형식에서 중심점과 크기를 읽는다.
        """
        if not hasattr(detection, 'bbox'):
            return None

        bbox = detection.bbox

        try:
            center_x = float(bbox.center.position.x)
            center_y = float(bbox.center.position.y)
            width = float(bbox.size.x)
            height = float(bbox.size.y)

            return center_x, center_y, width, height

        except AttributeError:
            return None


def main(args=None) -> None:
    rclpy.init(args=args)

    node = CupLocalizer()

    try:
        rclpy.spin(node)

    except KeyboardInterrupt:
        pass

    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()

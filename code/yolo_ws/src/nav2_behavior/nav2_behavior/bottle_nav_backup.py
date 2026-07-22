#!/usr/bin/env python3

import math
import statistics
from typing import Optional

import rclpy
from rclpy.qos import qos_profile_sensor_data

from geometry_msgs.msg import PointStamped, PoseStamped
from nav2_simple_commander.robot_navigator import BasicNavigator, TaskResult
from sensor_msgs.msg import LaserScan
from tf2_geometry_msgs import do_transform_point
from tf2_ros import Buffer, TransformException, TransformListener
from yolo_msgs.msg import DetectionArray


class BottleNavigator(BasicNavigator):
    """
    YOLO의 bottle 검출 방향과 LiDAR 스캔을 결합해 병 위치를 추정하고,
    병 앞 일정 거리까지 Nav2로 이동하는 노드.
    """

    def __init__(self) -> None:
        super().__init__(node_name='bottle_navigator')

        # ---------------------------------------------------------
        # 사용자 설정값
        # ---------------------------------------------------------
        self.target_class = 'bottle'

        self.image_width = 640.0
        self.horizontal_fov_deg = 78.0

        # 병 앞에서 멈출 거리
        self.stop_distance = 0.60

        # YOLO 검출 최소 신뢰도
        self.minimum_score = 0.50

        # 영상 방향과 LiDAR 방향을 매칭할 때 허용할 각도
        self.angle_tolerance_deg = 4.0

        # 너무 멀리 있는 LiDAR 값은 무시
        self.maximum_detection_distance = 4.0

        # 같은 병으로 연속 이동 명령이 나가는 것을 막음
        self.goal_sent = False

        # ---------------------------------------------------------
        # 내부 데이터
        # ---------------------------------------------------------
        self.latest_scan: Optional[LaserScan] = None
        self.bottle_bearing: Optional[float] = None
        self.bottle_score: float = 0.0

        self.goal_in_progress = False
        self.goal_description = ''

        # 카메라 초점거리 근사값
        hfov_rad = math.radians(self.horizontal_fov_deg)
        self.fx = self.image_width / (2.0 * math.tan(hfov_rad / 2.0))

        # ---------------------------------------------------------
        # TF
        # ---------------------------------------------------------
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(
            self.tf_buffer,
            self,
            spin_thread=False
        )

        # ---------------------------------------------------------
        # Subscribers
        # ---------------------------------------------------------
        self.detection_sub = self.create_subscription(
            DetectionArray,
            '/yolo/detections',
            self.detection_callback,
            10
        )

        self.scan_sub = self.create_subscription(
            LaserScan,
            '/scan',
            self.scan_callback,
            qos_profile_sensor_data
        )

        # 0.5초마다 병 위치 계산 및 Nav2 상태 확인
        self.timer = self.create_timer(0.5, self.timer_callback)

        self.get_logger().info('Bottle Navigator를 시작했습니다.')
        self.get_logger().info(
            f'대상={self.target_class}, '
            f'정지 거리={self.stop_distance:.2f} m, '
            f'HFOV={self.horizontal_fov_deg:.1f} deg'
        )

    def scan_callback(self, msg: LaserScan) -> None:
       """최신 LiDAR 데이터를 저장한다."""
       first_scan = self.latest_scan is None
       self.latest_scan = msg

       if first_scan:
           self.get_logger().info(
               f'LiDAR 수신 완료: frame_id={msg.header.frame_id}, '
               f'ranges={len(msg.ranges)}'
           )

    def detection_callback(self, msg: DetectionArray) -> None:
        """
        가장 신뢰도가 높은 bottle 검출 결과의 중심 픽셀을
        카메라 기준 수평 방위각으로 변환한다.
        """
        best_detection = None
        best_score = self.minimum_score

        for detection in msg.detections:
            if detection.class_name != self.target_class:
                continue

            if detection.score < best_score:
                continue

            best_detection = detection
            best_score = float(detection.score)

        if best_detection is None:
            return

        pixel_x = float(best_detection.bbox.center.position.x)

        # 영상 왼쪽은 로봇 기준 +y 방향이므로 양의 각도
        # 영상 오른쪽은 음의 각도
        self.bottle_bearing = math.atan(
            (self.image_width / 2.0 - pixel_x) / self.fx
        )
        self.bottle_score = best_score

        self.get_logger().info(
            f'병 검출: pixel_x={pixel_x:.1f}, '
            f'angle={math.degrees(self.bottle_bearing):.1f} deg, '
            f'score={best_score:.2f}'
        )

    def timer_callback(self) -> None:
        """센서 데이터가 준비되면 목표를 생성하고 Nav2 상태를 확인한다."""

        if self.goal_in_progress:
            self.check_navigation_result()
            return

        if self.goal_sent:
            return

        if self.latest_scan is None or self.bottle_bearing is None:
            return

        object_point_map = self.find_bottle_position()

        if object_point_map is None:
            self.get_logger().warning(
                'YOLO 방향과 일치하는 유효한 LiDAR 지점을 찾지 못했습니다.'
            )
            return

        goal_pose = self.create_approach_goal(object_point_map)

        if goal_pose is None:
            return

        self.get_logger().info(
            f'병 위치 추정: '
            f'x={object_point_map.point.x:.2f}, '
            f'y={object_point_map.point.y:.2f} [map]'
        )

        self.get_logger().info(
            f'이동 목표: '
            f'x={goal_pose.pose.position.x:.2f}, '
            f'y={goal_pose.pose.position.y:.2f} [map]'
        )

        self.goToPose(goal_pose)

        self.goal_sent = True
        self.goal_in_progress = True
        self.goal_description = (
            f'병 앞 {self.stop_distance:.2f} m 지점'
        )

    def find_bottle_position(self) -> Optional[PointStamped]:
        """
        모든 LiDAR 포인트를 camera_link로 변환한 뒤,
        YOLO가 계산한 방위각과 가까운 포인트를 찾는다.

        이 방식은 카메라와 LiDAR의 앞뒤 위치 차이도 TF를 통해 반영한다.
        """
        if self.latest_scan is None or self.bottle_bearing is None:
            return None

        scan = self.latest_scan

        try:
            scan_to_camera = self.tf_buffer.lookup_transform(
                'camera_link',
                scan.header.frame_id,
                rclpy.time.Time()
            )

            scan_to_map = self.tf_buffer.lookup_transform(
                'map',
                scan.header.frame_id,
                rclpy.time.Time()
            )

        except TransformException as error:
            self.get_logger().warning(f'TF 조회 실패: {error}')
            return None

        tolerance = math.radians(self.angle_tolerance_deg)

        candidates = []

        for index, distance in enumerate(scan.ranges):
            if not math.isfinite(distance):
                continue

            if distance <= max(scan.range_min, 0.05):
                continue

            if distance >= min(
                scan.range_max,
                self.maximum_detection_distance
            ):
                continue

            lidar_angle = scan.angle_min + index * scan.angle_increment

            scan_point = PointStamped()
            scan_point.header = scan.header
            scan_point.point.x = distance * math.cos(lidar_angle)
            scan_point.point.y = distance * math.sin(lidar_angle)
            scan_point.point.z = 0.0

            try:
                camera_point = do_transform_point(
                    scan_point,
                    scan_to_camera
                )
            except Exception:
                continue

            # 카메라 뒤쪽의 포인트는 제외
            if camera_point.point.x <= 0.0:
                continue

            candidate_bearing = math.atan2(
                camera_point.point.y,
                camera_point.point.x
            )

            angular_error = self.normalize_angle(
                candidate_bearing - self.bottle_bearing
            )

            if abs(angular_error) > tolerance:
                continue

            # 같은 각도에 벽과 병이 함께 있으면 가까운 물체를 우선한다.
            candidates.append(
                (
                    distance,
                    abs(angular_error),
                    scan_point
                )
            )

        if not candidates:
            return None

        # 가까운 후보부터 정렬
        candidates.sort(key=lambda item: (item[0], item[1]))

        # 노이즈 완화를 위해 가까운 후보 최대 5개 사용
        selected = candidates[:5]

        map_x_values = []
        map_y_values = []

        for _, _, scan_point in selected:
            map_point = do_transform_point(
                scan_point,
                scan_to_map
            )

            map_x_values.append(map_point.point.x)
            map_y_values.append(map_point.point.y)

        result = PointStamped()
        result.header.frame_id = 'map'
        result.header.stamp = self.get_clock().now().to_msg()
        result.point.x = statistics.median(map_x_values)
        result.point.y = statistics.median(map_y_values)
        result.point.z = 0.0

        return result

    def create_approach_goal(
        self,
        object_point_map: PointStamped
    ) -> Optional[PoseStamped]:
        """
        현재 로봇 위치와 병 위치 사이의 직선상에서,
        병보다 stop_distance만큼 앞에 있는 Nav2 목표를 생성한다.
        """
        try:
            map_to_base = self.tf_buffer.lookup_transform(
                'map',
                'base_link',
                rclpy.time.Time()
            )
        except TransformException as error:
            self.get_logger().warning(f'로봇 위치 TF 조회 실패: {error}')
            return None

        robot_x = map_to_base.transform.translation.x
        robot_y = map_to_base.transform.translation.y

        object_x = object_point_map.point.x
        object_y = object_point_map.point.y

        dx = object_x - robot_x
        dy = object_y - robot_y

        distance_to_object = math.hypot(dx, dy)

        if distance_to_object <= self.stop_distance:
            self.get_logger().info(
                f'이미 병과 {distance_to_object:.2f} m 거리입니다. '
                '추가 이동하지 않습니다.'
            )
            self.goal_sent = True
            return None

        direction_x = dx / distance_to_object
        direction_y = dy / distance_to_object

        goal_x = object_x - self.stop_distance * direction_x
        goal_y = object_y - self.stop_distance * direction_y

        yaw = math.atan2(
            object_y - goal_y,
            object_x - goal_x
        )

        goal = PoseStamped()
        goal.header.frame_id = 'map'
        goal.header.stamp = self.get_clock().now().to_msg()

        goal.pose.position.x = goal_x
        goal.pose.position.y = goal_y
        goal.pose.position.z = 0.0

        goal.pose.orientation.x = 0.0
        goal.pose.orientation.y = 0.0
        goal.pose.orientation.z = math.sin(yaw / 2.0)
        goal.pose.orientation.w = math.cos(yaw / 2.0)

        return goal

    def check_navigation_result(self) -> None:
        """진행 중인 Nav2 작업 상태를 확인한다."""

        if self.isTaskComplete():
            result = self.getResult()

            if result == TaskResult.SUCCEEDED:
                self.get_logger().info(
                    f'이동 완료: {self.goal_description}'
                )

            elif result == TaskResult.CANCELED:
                self.get_logger().warning('이동이 취소되었습니다.')

            elif result == TaskResult.FAILED:
                self.get_logger().error('이동에 실패했습니다.')

            else:
                self.get_logger().warning(
                    f'알 수 없는 Nav2 결과: {result}'
                )

            self.goal_in_progress = False
            return

        feedback = self.getFeedback()

        if feedback is not None:
            remaining = feedback.distance_remaining

            self.get_logger().info(
                f'병까지 이동 중 · 남은 경로: {remaining:.2f} m'
            )

    @staticmethod
    def normalize_angle(angle: float) -> float:
        """각도를 -pi부터 +pi 범위로 변환한다."""
        return math.atan2(math.sin(angle), math.cos(angle))


def main(args=None) -> None:
    rclpy.init(args=args)

    navigator = BottleNavigator()

    try:
        navigator.get_logger().info(
            'Nav2가 활성화될 때까지 기다립니다.'
        )

        navigator.waitUntilNav2Active()

        navigator.get_logger().info(
            'Nav2 준비 완료. 병을 탐색합니다.'
        )

        rclpy.spin(navigator)

    except KeyboardInterrupt:
        navigator.get_logger().info('사용자 요청으로 종료합니다.')

    finally:
        navigator.destroy_node()

        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()

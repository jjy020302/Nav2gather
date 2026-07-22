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
    YOLO bottle 검출 방향과 LiDAR 스캔을 결합하여 병 위치를 추정하고,
    병 앞 일정 거리까지 Nav2로 이동하는 노드.
    """

    def __init__(self) -> None:
        super().__init__(node_name='bottle_navigator')

        # 사용자 설정
        self.target_class = 'bottle'
        self.image_width = 640.0
        self.horizontal_fov_deg = 78.0
        self.stop_distance = 0.60
        self.minimum_score = 0.50

        # LiDAR 필터 설정
        self.minimum_object_distance = 0.20
        self.maximum_detection_distance = 2.50
        self.angle_tolerance_deg = 2.5
        self.minimum_cluster_points = 2

        # 내부 상태
        self.latest_scan: Optional[LaserScan] = None
        self.bottle_bearing: Optional[float] = None
        self.bottle_score = 0.0

        self.pending_goal: Optional[PoseStamped] = None
        self.goal_sent = False
        self.goal_in_progress = False
        self.goal_description = ''

        # 로그 반복 제한
        self.last_feedback_log_time = 0.0

        # 카메라 초점거리 근사
        hfov_rad = math.radians(self.horizontal_fov_deg)
        self.fx = self.image_width / (
            2.0 * math.tan(hfov_rad / 2.0)
        )

        # TF
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(
            self.tf_buffer,
            self,
            spin_thread=False
        )

        # Subscribers
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

        # 병 위치 계산용 타이머
        self.timer = self.create_timer(
            0.5,
            self.timer_callback
        )

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
                f'LiDAR 수신 완료: '
                f'frame_id={msg.header.frame_id}, '
                f'ranges={len(msg.ranges)}'
            )

    def detection_callback(self, msg: DetectionArray) -> None:
        """
        가장 신뢰도가 높은 bottle 검출 결과를 선택하고
        중심 픽셀을 수평 방위각으로 변환한다.
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

        pixel_x = float(
            best_detection.bbox.center.position.x
        )

        # 영상 왼쪽: 양의 각도
        # 영상 오른쪽: 음의 각도
        self.bottle_bearing = math.atan(
            (self.image_width / 2.0 - pixel_x) / self.fx
        )
        self.bottle_score = best_score

        self.get_logger().info(
            f'병 검출: '
            f'pixel_x={pixel_x:.1f}, '
            f'angle={math.degrees(self.bottle_bearing):.1f} deg, '
            f'score={best_score:.2f}'
        )

    def timer_callback(self) -> None:
        """
        병 위치와 Nav2 목표를 계산한다.

        여기서는 goToPose()를 호출하지 않고,
        pending_goal에 목표만 저장한다.
        """
        if self.goal_in_progress:
            return

        if self.goal_sent:
            return

        if self.pending_goal is not None:
            return

        if self.latest_scan is None:
            return

        if self.bottle_bearing is None:
            return

        object_point_map = self.find_bottle_position()

        if object_point_map is None:
            self.get_logger().warning(
                '병 방향에서 신뢰할 수 있는 LiDAR 물체를 '
                '찾지 못했습니다.'
            )
            return

        goal_pose = self.create_approach_goal(
            object_point_map
        )

        if goal_pose is None:
            return

        self.get_logger().info(
            f'병 위치 후보: '
            f'x={object_point_map.point.x:.2f}, '
            f'y={object_point_map.point.y:.2f} [map]'
        )

        self.get_logger().info(
            f'이동 목표 후보: '
            f'x={goal_pose.pose.position.x:.2f}, '
            f'y={goal_pose.pose.position.y:.2f} [map]'
        )

        self.pending_goal = goal_pose

    def find_bottle_position(
        self
    ) -> Optional[PointStamped]:
        """
        YOLO 방향 근처 LiDAR 점을 찾고,
        연속된 거리값으로 이루어진 클러스터를 선택한다.
        """
        if self.latest_scan is None:
            return None

        if self.bottle_bearing is None:
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
            self.get_logger().warning(
                f'TF 조회 실패: {error}'
            )
            return None

        tolerance = math.radians(
            self.angle_tolerance_deg
        )

        candidates = []

        for index, distance in enumerate(scan.ranges):
            if not math.isfinite(distance):
                continue

            if distance < self.minimum_object_distance:
                continue

            if distance > self.maximum_detection_distance:
                continue

            lidar_angle = (
                scan.angle_min
                + index * scan.angle_increment
            )

            scan_point = PointStamped()
            scan_point.header = scan.header
            scan_point.point.x = (
                distance * math.cos(lidar_angle)
            )
            scan_point.point.y = (
                distance * math.sin(lidar_angle)
            )
            scan_point.point.z = 0.0

            try:
                camera_point = do_transform_point(
                    scan_point,
                    scan_to_camera
                )
            except Exception:
                continue

            # 카메라 뒤쪽 포인트 제외
            if camera_point.point.x <= 0.0:
                continue

            candidate_bearing = math.atan2(
                camera_point.point.y,
                camera_point.point.x
            )

            angular_error = self.normalize_angle(
                candidate_bearing
                - self.bottle_bearing
            )

            if abs(angular_error) > tolerance:
                continue

            candidates.append({
                'index': index,
                'distance': float(distance),
                'angular_error': abs(angular_error),
                'scan_point': scan_point,
            })

        if not candidates:
            return None

        candidates.sort(
            key=lambda item: item['index']
        )

        # 연속 포인트를 클러스터로 묶기
        clusters = []
        current_cluster = [candidates[0]]

        for candidate in candidates[1:]:
            previous = current_cluster[-1]

            index_gap = (
                candidate['index']
                - previous['index']
            )

            distance_gap = abs(
                candidate['distance']
                - previous['distance']
            )

            if (
                index_gap <= 2
                and distance_gap <= 0.18
            ):
                current_cluster.append(candidate)
            else:
                clusters.append(current_cluster)
                current_cluster = [candidate]

        clusters.append(current_cluster)

        valid_clusters = [
            cluster
            for cluster in clusters
            if len(cluster)
            >= self.minimum_cluster_points
        ]

        if not valid_clusters:
            self.get_logger().warning(
                '병 방향에 LiDAR 점은 있지만 '
                '연속된 물체 클러스터가 없습니다.'
            )
            return None

        def cluster_score(cluster) -> float:
            median_distance = statistics.median(
                point['distance']
                for point in cluster
            )

            median_error = statistics.median(
                point['angular_error']
                for point in cluster
            )

            # 각도 오차를 더 중요하게 평가
            return (
                median_error * 3.0
                + median_distance * 0.15
            )

        selected_cluster = min(
            valid_clusters,
            key=cluster_score
        )

        selected_distances = [
            point['distance']
            for point in selected_cluster
        ]

        selected_indices = [
            point['index']
            for point in selected_cluster
        ]

        self.get_logger().info(
            f'LiDAR 클러스터 선택: '
            f'points={len(selected_cluster)}, '
            f'distance='
            f'{statistics.median(selected_distances):.2f} m, '
            f'index='
            f'{min(selected_indices)}~'
            f'{max(selected_indices)}'
        )

        map_x_values = []
        map_y_values = []

        for candidate in selected_cluster:
            map_point = do_transform_point(
                candidate['scan_point'],
                scan_to_map
            )

            map_x_values.append(
                map_point.point.x
            )
            map_y_values.append(
                map_point.point.y
            )

        result = PointStamped()
        result.header.frame_id = 'map'
        result.header.stamp = (
            self.get_clock().now().to_msg()
        )
        result.point.x = statistics.median(
            map_x_values
        )
        result.point.y = statistics.median(
            map_y_values
        )
        result.point.z = 0.0

        return result

    def create_approach_goal(
        self,
        object_point_map: PointStamped
    ) -> Optional[PoseStamped]:
        """
        병 위치에서 stop_distance만큼 떨어진
        접근 목표를 생성한다.
        """
        try:
            map_to_base = self.tf_buffer.lookup_transform(
                'map',
                'base_link',
                rclpy.time.Time()
            )

        except TransformException as error:
            self.get_logger().warning(
                f'로봇 위치 TF 조회 실패: {error}'
            )
            return None

        robot_x = (
            map_to_base.transform.translation.x
        )
        robot_y = (
            map_to_base.transform.translation.y
        )

        object_x = object_point_map.point.x
        object_y = object_point_map.point.y

        dx = object_x - robot_x
        dy = object_y - robot_y

        distance_to_object = math.hypot(dx, dy)

        if distance_to_object <= self.stop_distance:
            self.get_logger().info(
                f'이미 병과 '
                f'{distance_to_object:.2f} m 거리입니다. '
                '추가 이동하지 않습니다.'
            )
            self.goal_sent = True
            return None

        direction_x = dx / distance_to_object
        direction_y = dy / distance_to_object

        goal_x = (
            object_x
            - self.stop_distance * direction_x
        )
        goal_y = (
            object_y
            - self.stop_distance * direction_y
        )

        yaw = math.atan2(
            object_y - goal_y,
            object_x - goal_x
        )

        goal = PoseStamped()
        goal.header.frame_id = 'map'
        goal.header.stamp = (
            self.get_clock().now().to_msg()
        )

        goal.pose.position.x = goal_x
        goal.pose.position.y = goal_y
        goal.pose.position.z = 0.0

        goal.pose.orientation.x = 0.0
        goal.pose.orientation.y = 0.0
        goal.pose.orientation.z = (
            math.sin(yaw / 2.0)
        )
        goal.pose.orientation.w = (
            math.cos(yaw / 2.0)
        )

        return goal

    @staticmethod
    def normalize_angle(angle: float) -> float:
        """각도를 -pi ~ +pi 범위로 정규화한다."""
        return math.atan2(
            math.sin(angle),
            math.cos(angle)
        )


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

        while rclpy.ok():
            # 콜백 처리
            rclpy.spin_once(
                navigator,
                timeout_sec=0.1
            )

            # 콜백 밖에서 Nav2 목표 전송
            if (
                navigator.pending_goal is not None
                and not navigator.goal_in_progress
                and not navigator.goal_sent
            ):
                goal_pose = navigator.pending_goal
                navigator.pending_goal = None

                navigator.get_logger().info(
                    f'Nav2 목표 전송: '
                    f'x={goal_pose.pose.position.x:.2f}, '
                    f'y={goal_pose.pose.position.y:.2f}'
                )

                navigator.goToPose(goal_pose)

                navigator.goal_sent = True
                navigator.goal_in_progress = True
                navigator.goal_description = (
                    f'병 앞 '
                    f'{navigator.stop_distance:.2f} m 지점'
                )

            if navigator.goal_in_progress:
                if navigator.isTaskComplete():
                    result = navigator.getResult()

                    if result == TaskResult.SUCCEEDED:
                        navigator.get_logger().info(
                            '병 앞 목표 지점까지 '
                            '이동을 완료했습니다.'
                        )

                    elif result == TaskResult.CANCELED:
                        navigator.get_logger().warning(
                            '병 이동 작업이 '
                            '취소되었습니다.'
                        )

                    elif result == TaskResult.FAILED:
                        navigator.get_logger().error(
                            '병 이동 작업에 '
                            '실패했습니다.'
                        )

                    else:
                        navigator.get_logger().warning(
                            f'알 수 없는 결과: {result}'
                        )

                    navigator.goal_in_progress = False

                else:
                    feedback = navigator.getFeedback()

                    if feedback is not None:
                        now = (
                            navigator.get_clock()
                            .now()
                            .nanoseconds
                            / 1e9
                        )

                        if (
                            now
                            - navigator.last_feedback_log_time
                            >= 1.0
                        ):
                            navigator.get_logger().info(
                                f'이동 중 · 남은 경로: '
                                f'{feedback.distance_remaining:.2f} m'
                            )
                            navigator.last_feedback_log_time = now

    except KeyboardInterrupt:
        navigator.get_logger().info(
            '사용자 요청으로 종료합니다.'
        )

    finally:
        navigator.destroy_node()

        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()

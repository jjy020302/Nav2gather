#!/usr/bin/env python3

import math
import statistics
from collections import deque
from enum import Enum, auto

import rclpy
from geometry_msgs.msg import PointStamped, PoseStamped, TwistStamped
from nav2_simple_commander.robot_navigator import (
    BasicNavigator,
    TaskResult,
)
from rclpy.qos import qos_profile_sensor_data
from tf2_geometry_msgs import do_transform_point
from tf2_ros import Buffer, TransformException, TransformListener


class BehaviorState(Enum):
    """Bottle behavior 동작 상태."""

    SEARCHING = auto()
    ALIGNING = auto()
    PREPARING_GOAL = auto()
    NAVIGATING = auto()
    COOLDOWN = auto()
    STOPPED = auto()


class BottleBehavior(BasicNavigator):
    """
    bottle을 탐색한 뒤 해당 위치 앞으로 이동하고,
    도착하면 다시 다음 bottle을 탐색하는 통합 Behavior 노드.
    """

    def __init__(self):
        super().__init__(node_name='bottle_behavior')

        # ---------------------------------------------------------
        # 사용자 설정값
        # ---------------------------------------------------------

        # 좌표 프레임
        self.global_frame = 'map'
        self.robot_frame = 'base_link'

        # bottle 앞에서 멈출 거리
        self.stop_distance = 0.10

        # bottle을 찾을 때 제자리 회전 속도
        self.search_angular_speed = 0.22

        # bottle이 카메라 중앙에 들어왔다고 판단하는 각도 허용 오차
        self.alignment_angle_tolerance = 0.06

        # 중앙 정렬 시 제자리 회전 속도
        self.alignment_angular_speed = 0.12

        # 중앙 정렬 제한 시간
        self.alignment_timeout = 8.0

        # 목표 생성에 사용할 좌표 샘플 수
        self.required_samples = 5

        # 좌표 샘플 유효 시간
        self.sample_timeout = 1.5

        # Nav2 실패 시 재시도 횟수
        self.max_retries = 2

        # 도착 후 같은 bottle을 다시 목표로 잡지 않도록 대기하는 시간
        self.cooldown_duration = 3.0

        # 너무 가깝거나 잘못된 좌표를 제거하기 위한 범위
        self.minimum_bottle_distance = 0.20
        self.maximum_bottle_distance = 4.00

        # 새 bottle을 찾지 못했을 때 탐색을 중단하는 기준
        # search_attempt_duration은 약 한 바퀴 회전에 해당한다.
        self.max_search_attempts = 3
        self.search_attempt_duration = 30.0

        # ---------------------------------------------------------
        # 내부 상태
        # ---------------------------------------------------------

        self.state = BehaviorState.SEARCHING

        self.bottle_samples = deque(
            maxlen=self.required_samples
        )

        self.last_bottle_time = None
        self.cooldown_start_time = None

        self.retry_count = 0
        self.current_goal = None

        self.alignment_angle = None
        self.alignment_start_time = None

        # 도착한 모든 bottle 좌표를 기억해 같은 bottle 재탐색 방지
        self.reached_bottles = []
        self.current_target_bottle = None
        self.ignore_reached_radius = 0.60

        # 새 bottle 탐색 횟수 관리
        self.search_attempt_count = 0
        self.search_attempt_start_time = self.get_clock().now()

        # ---------------------------------------------------------
        # TF
        # ---------------------------------------------------------

        self.tf_buffer = Buffer()

        self.tf_listener = TransformListener(
            self.tf_buffer,
            self
        )

        # ---------------------------------------------------------
        # Publisher / Subscriber
        # ---------------------------------------------------------

        # TurtleBot3의 /cmd_vel 타입은 TwistStamped
        self.cmd_vel_pub = self.create_publisher(
            TwistStamped,
            '/cmd_vel',
            10
        )

        # bottle localizer가 발행하는 좌표
        self.bottle_sub = self.create_subscription(
            PointStamped,
            '/bottle/point',
            self.bottle_callback,
            qos_profile_sensor_data
        )

        self.get_logger().info(
            'Bottle Behavior 시작'
        )

        self.get_logger().info(
            f'상태=SEARCHING, 정지 거리={self.stop_distance:.2f} m, '
            f'탐색 회전 속도={self.search_angular_speed:.2f} rad/s'
        )

    # =============================================================
    # TwistStamped 명령
    # =============================================================

    def create_velocity_command(
        self,
        linear_x=0.0,
        angular_z=0.0
    ):
        """TurtleBot3용 TwistStamped 명령을 생성한다."""

        cmd = TwistStamped()

        cmd.header.stamp = self.get_clock().now().to_msg()
        cmd.header.frame_id = self.robot_frame

        cmd.twist.linear.x = float(linear_x)
        cmd.twist.linear.y = 0.0
        cmd.twist.linear.z = 0.0

        cmd.twist.angular.x = 0.0
        cmd.twist.angular.y = 0.0
        cmd.twist.angular.z = float(angular_z)

        return cmd

    def publish_search_rotation(self):
        """bottle 탐색을 위한 제자리 회전 명령."""

        cmd = self.create_velocity_command(
            angular_z=self.search_angular_speed
        )

        self.cmd_vel_pub.publish(cmd)

    def publish_stop(self):
        """로봇 정지 명령."""

        cmd = self.create_velocity_command(
            linear_x=0.0,
            angular_z=0.0
        )

        self.cmd_vel_pub.publish(cmd)

    # =============================================================
    # Bottle 좌표 수신
    # =============================================================

    def bottle_callback(self, msg):
        """
        bottle 좌표를 먼저 map 프레임으로 변환해 이미 방문한 bottle인지
        확인한 뒤, 필요한 경우에만 카메라 중앙 정렬과 좌표 수집을 수행한다.
        """

        if self.state not in (
            BehaviorState.SEARCHING,
            BehaviorState.ALIGNING,
            BehaviorState.PREPARING_GOAL,
        ):
            return

        try:
            bottle_map = self.transform_point_to_map(msg)

        except TransformException as error:
            self.get_logger().warn(
                f'bottle 좌표 TF 변환 실패: {error}',
                throttle_duration_sec=1.0
            )
            return

        x = bottle_map.point.x
        y = bottle_map.point.y

        try:
            robot_x, robot_y, _ = self.get_robot_pose()

        except TransformException as error:
            self.get_logger().warn(
                f'로봇 위치 TF 확인 실패: {error}',
                throttle_duration_sec=1.0
            )
            return

        distance = math.hypot(
            x - robot_x,
            y - robot_y
        )

        # 이미 도착한 bottle인지 중앙 정렬보다 먼저 확인한다.
        for index, (reached_x, reached_y) in enumerate(
            self.reached_bottles,
            start=1
        ):
            distance_from_reached = math.hypot(
                x - reached_x,
                y - reached_y
            )

            if distance_from_reached < self.ignore_reached_radius:
                self.publish_stop()

                # 이미 방문한 bottle을 보고 정렬 중이었다면 즉시 탐색으로 복귀한다.
                if self.state == BehaviorState.ALIGNING:
                    self.alignment_angle = None
                    self.alignment_start_time = None
                    self.bottle_samples.clear()
                    self.state = BehaviorState.SEARCHING

                self.get_logger().info(
                    f'이미 도착한 bottle #{index} 무시: '
                    f'거리={distance_from_reached:.2f} m',
                    throttle_duration_sec=1.0
                )
                return

        # 비정상적인 거리 값 제거
        if distance > self.maximum_bottle_distance:
            self.get_logger().warn(
                f'bottle 좌표 거리 범위 초과: {distance:.2f} m',
                throttle_duration_sec=1.0
            )
            return

        if distance < self.minimum_bottle_distance:
            self.get_logger().warn(
                f'bottle 좌표 거리 범위 초과: {distance:.2f} m',
                throttle_duration_sec=1.0
            )
            return

        # 방문하지 않은 bottle이고 충분히 멀리 있을 때만 중앙 정렬한다.
        if (
            msg.header.frame_id == 'camera_optical_frame'
            and distance > self.stop_distance
        ):
            if msg.point.z <= 0.0:
                return

            self.alignment_angle = math.atan2(
                msg.point.x,
                msg.point.z
            )

            if abs(self.alignment_angle) > self.alignment_angle_tolerance:
                if self.state != BehaviorState.ALIGNING:
                    self.alignment_start_time = self.get_clock().now()
                    self.bottle_samples.clear()

                    self.get_logger().info(
                        '새 bottle 인식 → 카메라 중앙 정렬을 시작합니다.'
                    )

                self.state = BehaviorState.ALIGNING

                self.cmd_vel_pub.publish(
                    self.create_velocity_command(
                        angular_z=-math.copysign(
                            self.alignment_angular_speed,
                            self.alignment_angle
                        )
                    )
                )

                self.get_logger().info(
                    f'bottle 중앙 정렬 중: '
                    f'각도 오차={math.degrees(self.alignment_angle):.1f} deg, '
                    f'거리={distance:.2f} m',
                    throttle_duration_sec=0.5
                )
                return

            if self.state in (
                BehaviorState.SEARCHING,
                BehaviorState.ALIGNING,
            ):
                self.publish_stop()
                self.bottle_samples.clear()
                self.last_bottle_time = None
                self.alignment_start_time = None
                self.state = BehaviorState.PREPARING_GOAL

                self.get_logger().info(
                    f'bottle 중앙 정렬 완료: '
                    f'각도 오차={math.degrees(self.alignment_angle):.1f} deg '
                    '→ 좌표 재수집 시작'
                )

        self.last_bottle_time = self.get_clock().now()

        self.bottle_samples.append(
            (x, y)
        )

        self.state = BehaviorState.PREPARING_GOAL

        self.publish_stop()

        self.get_logger().info(
            f'bottle 좌표 수집: '
            f'{len(self.bottle_samples)}/{self.required_samples}, '
            f'map=({x:.2f}, {y:.2f}), '
            f'거리={distance:.2f} m',
            throttle_duration_sec=0.5
        )

    def transform_point_to_map(self, point_msg):
        """PointStamped 좌표를 map 프레임으로 변환한다."""

        if point_msg.header.frame_id == self.global_frame:
            return point_msg

        transform = self.tf_buffer.lookup_transform(
            self.global_frame,
            point_msg.header.frame_id,
            rclpy.time.Time(),
            timeout=rclpy.duration.Duration(seconds=0.3)
        )

        return do_transform_point(
            point_msg,
            transform
        )

    def get_robot_pose(self):
        """현재 로봇의 map 좌표와 yaw를 반환한다."""

        transform = self.tf_buffer.lookup_transform(
            self.global_frame,
            self.robot_frame,
            rclpy.time.Time(),
            timeout=rclpy.duration.Duration(seconds=0.3)
        )

        x = transform.transform.translation.x
        y = transform.transform.translation.y

        q = transform.transform.rotation

        yaw = math.atan2(
            2.0 * (q.w * q.z + q.x * q.y),
            1.0 - 2.0 * (q.y * q.y + q.z * q.z)
        )

        return x, y, yaw

    # =============================================================
    # 목표 생성
    # =============================================================

    def create_approach_goal(
        self,
        bottle_x,
        bottle_y
    ):
        """
        bottle 위치 바로 앞이 아니라 stop_distance만큼 떨어진
        접근 지점을 Nav2 목표로 생성한다.
        """

        robot_x, robot_y, _ = self.get_robot_pose()

        dx = bottle_x - robot_x
        dy = bottle_y - robot_y

        distance = math.hypot(dx, dy)

        if distance <= self.stop_distance:
            self.get_logger().info(
                f'bottle까지 이미 충분히 가까움: {distance:.2f} m'
            )
            return None

        unit_x = dx / distance
        unit_y = dy / distance

        goal_x = bottle_x - (
            unit_x * self.stop_distance
        )

        goal_y = bottle_y - (
            unit_y * self.stop_distance
        )

        # 도착 후 bottle을 바라보도록 방향 설정
        goal_yaw = math.atan2(
            bottle_y - goal_y,
            bottle_x - goal_x
        )

        goal = PoseStamped()

        goal.header.frame_id = self.global_frame
        goal.header.stamp = self.get_clock().now().to_msg()

        goal.pose.position.x = goal_x
        goal.pose.position.y = goal_y
        goal.pose.position.z = 0.0

        goal.pose.orientation.x = 0.0
        goal.pose.orientation.y = 0.0
        goal.pose.orientation.z = math.sin(
            goal_yaw / 2.0
        )
        goal.pose.orientation.w = math.cos(
            goal_yaw / 2.0
        )

        self.get_logger().info(
            f'bottle 평균 좌표=({bottle_x:.2f}, {bottle_y:.2f})'
        )

        self.get_logger().info(
            f'Nav2 목표 좌표=({goal_x:.2f}, {goal_y:.2f}), '
            f'물병 기준 목표 이격 거리={self.stop_distance:.2f} m'
        )

        return goal

    # =============================================================
    # Behavior 상태 처리
    # =============================================================

    def behavior_loop(self):
        """현재 상태에 따라 탐색, 목표 생성, 이동을 처리한다."""

        if self.state == BehaviorState.SEARCHING:
            self.handle_searching()

        elif self.state == BehaviorState.ALIGNING:
            self.handle_aligning()

        elif self.state == BehaviorState.PREPARING_GOAL:
            self.handle_preparing_goal()

        elif self.state == BehaviorState.NAVIGATING:
            self.handle_navigating()

        elif self.state == BehaviorState.COOLDOWN:
            self.handle_cooldown()

        elif self.state == BehaviorState.STOPPED:
            self.publish_stop()

    def handle_searching(self):
        """bottle이 없을 때 탐색 회전하고 최대 횟수에서 중단한다."""

        if self.search_attempt_start_time is None:
            self.search_attempt_start_time = self.get_clock().now()

        elapsed = (
            self.get_clock().now() -
            self.search_attempt_start_time
        ).nanoseconds / 1e9

        if elapsed >= self.search_attempt_duration:
            self.search_attempt_count += 1
            self.search_attempt_start_time = self.get_clock().now()

            self.get_logger().info(
                f'bottle 탐색 {self.search_attempt_count}/'
                f'{self.max_search_attempts}회 완료'
            )

            if self.search_attempt_count >= self.max_search_attempts:
                self.publish_stop()
                self.state = BehaviorState.STOPPED

                self.get_logger().warn(
                    '새 bottle을 찾지 못해 탐색을 중단합니다.'
                )
                return

        self.publish_search_rotation()

        self.get_logger().info(
            f'bottle 탐색 중 → 제자리 회전 '
            f'({self.search_attempt_count + 1}/'
            f'{self.max_search_attempts}회)',
            throttle_duration_sec=2.0
        )

    def handle_aligning(self):
        """bottle이 카메라 중앙에 오도록 제자리 회전한다."""

        if self.alignment_start_time is None:
            self.alignment_start_time = self.get_clock().now()

        elapsed = (
            self.get_clock().now() -
            self.alignment_start_time
        ).nanoseconds / 1e9

        if elapsed > self.alignment_timeout:
            self.get_logger().warn(
                'bottle 중앙 정렬 시간 초과 → 다시 탐색'
            )
            self.reset_to_search()
            return

        if self.alignment_angle is None:
            self.publish_stop()
            return

        self.cmd_vel_pub.publish(
            self.create_velocity_command(
                angular_z=-math.copysign(
                    self.alignment_angular_speed,
                    self.alignment_angle
                )
            )
        )

    def handle_preparing_goal(self):
        """중앙 정렬 후 충분한 bottle 좌표를 모아 Nav2 목표를 생성한다."""

        # 마지막 좌표 수신 후 오래 지났으면 다시 탐색
        if self.last_bottle_time is None:
            self.reset_to_search(new_search=True)
            return

        elapsed = (
            self.get_clock().now() -
            self.last_bottle_time
        ).nanoseconds / 1e9

        if elapsed > self.sample_timeout:
            self.get_logger().warn(
                'bottle 좌표 수집 시간 초과 → 다시 탐색'
            )

            self.reset_to_search()
            return

        # 아직 샘플이 부족하면 정지한 상태로 좌표를 더 받는다.
        if len(self.bottle_samples) < self.required_samples:
            self.publish_stop()
            return

        bottle_x = statistics.median(
            sample[0]
            for sample in self.bottle_samples
        )

        bottle_y = statistics.median(
            sample[1]
            for sample in self.bottle_samples
        )

        try:
            goal = self.create_approach_goal(
                bottle_x,
                bottle_y
            )

        except TransformException as error:
            self.get_logger().warn(
                f'Nav2 목표 생성 실패: {error}'
            )

            self.reset_to_search()
            return

        if goal is None:
            self.publish_stop()

            # 실제로 충분히 가까운 경우에만 해당 bottle을 도착 목록에 등록한다.
            self.reached_bottles.append((bottle_x, bottle_y))

            self.get_logger().info(
                '현재 위치에서 bottle에 충분히 가까움 → 도착 처리'
            )

            self.get_logger().info(
                f'도착한 bottle #{len(self.reached_bottles)} 등록: '
                f'({bottle_x:.2f}, {bottle_y:.2f}), '
                f'무시 반경={self.ignore_reached_radius:.2f} m'
            )

            self.start_cooldown()
            return

        self.current_goal = goal
        self.current_target_bottle = (bottle_x, bottle_y)
        self.retry_count = 0

        self.publish_stop()

        self.get_logger().info(
            'Nav2에 bottle 접근 목표를 전송합니다.'
        )

        self.goToPose(goal)

        self.state = BehaviorState.NAVIGATING

    def handle_navigating(self):
        """Nav2 이동 결과를 확인한다."""

        if not self.isTaskComplete():
            feedback = self.getFeedback()

            if (
                feedback is not None
                and feedback.distance_remaining is not None
            ):
                self.get_logger().info(
                    f'bottle까지 이동 중, '
                    f'남은 거리={feedback.distance_remaining:.2f} m',
                    throttle_duration_sec=2.0
                )

            return

        result = self.getResult()

        if result == TaskResult.SUCCEEDED:
            self.publish_stop()

            self.get_logger().info(
                'bottle 접근 목표 도착 완료!'
            )

            if self.current_target_bottle is not None:
                self.reached_bottles.append(
                    self.current_target_bottle
                )

                reached_x, reached_y = self.current_target_bottle

                self.get_logger().info(
                    f'도착한 bottle #{len(self.reached_bottles)} 등록: '
                    f'({reached_x:.2f}, {reached_y:.2f}), '
                    f'무시 반경={self.ignore_reached_radius:.2f} m'
                )

            self.start_cooldown()

        elif result == TaskResult.CANCELED:
            self.publish_stop()

            self.get_logger().warn(
                'Nav2 이동이 취소되었습니다.'
            )

            self.reset_to_search()

        elif result == TaskResult.FAILED:
            self.publish_stop()

            if (
                self.retry_count < self.max_retries
                and self.current_goal is not None
            ):
                self.retry_count += 1

                self.get_logger().warn(
                    f'Nav2 이동 실패 → 재시도 '
                    f'{self.retry_count}/{self.max_retries}'
                )

                self.goToPose(
                    self.current_goal
                )

            else:
                self.get_logger().error(
                    'Nav2 이동 재시도 횟수 초과 → 다시 탐색'
                )

                self.reset_to_search()

        else:
            self.publish_stop()

            self.get_logger().error(
                f'알 수 없는 Nav2 결과: {result}'
            )

            self.reset_to_search()

    def start_cooldown(self):
        """도착 후 잠시 대기한 뒤 다음 bottle 탐색 준비."""

        self.publish_stop()

        self.cooldown_start_time = self.get_clock().now()
        self.state = BehaviorState.COOLDOWN

        self.bottle_samples.clear()
        self.last_bottle_time = None
        self.current_goal = None
        self.current_target_bottle = None

        self.get_logger().info(
            f'{self.cooldown_duration:.1f}초 정지 후 '
            '다음 bottle 탐색을 시작합니다.'
        )

    def handle_cooldown(self):
        """도착 직후 같은 bottle 재검출을 방지하기 위한 대기."""

        self.publish_stop()

        if self.cooldown_start_time is None:
            self.reset_to_search()
            return

        elapsed = (
            self.get_clock().now() -
            self.cooldown_start_time
        ).nanoseconds / 1e9

        if elapsed >= self.cooldown_duration:
            self.get_logger().info(
                '다음 bottle 탐색 시작'
            )

            self.reset_to_search(new_search=True)

    def reset_to_search(self, new_search=False):
        """모든 목표 정보를 초기화하고 탐색 상태로 복귀."""

        self.publish_stop()

        self.bottle_samples.clear()
        self.last_bottle_time = None
        self.cooldown_start_time = None

        self.current_goal = None
        self.current_target_bottle = None
        self.retry_count = 0

        self.alignment_angle = None
        self.alignment_start_time = None

        if new_search:
            self.search_attempt_count = 0
            self.search_attempt_start_time = self.get_clock().now()

        self.state = BehaviorState.SEARCHING

    def destroy_node(self):
        """노드 종료 시 Nav2 목표를 취소하고 로봇 정지."""

        try:
            if self.state == BehaviorState.NAVIGATING:
                self.cancelTask()

        except Exception:
            pass

        self.publish_stop()

        super().destroy_node()


def main(args=None):
    rclpy.init(args=args)

    navigator = BottleBehavior()

    try:
        navigator.get_logger().info(
            'Nav2 활성화를 기다립니다.'
        )

        navigator.waitUntilNav2Active()

        navigator.get_logger().info(
            'Nav2 활성화 완료 → bottle 탐색 시작'
        )

        while rclpy.ok():
            rclpy.spin_once(
                navigator,
                timeout_sec=0.1
            )

            navigator.behavior_loop()

    except KeyboardInterrupt:
        navigator.get_logger().info(
            'Bottle Behavior를 종료합니다.'
        )

    finally:
        try:
            navigator.publish_stop()

            if navigator.state == BehaviorState.NAVIGATING:
                navigator.cancelTask()

        except Exception:
            pass

        navigator.destroy_node()

        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()

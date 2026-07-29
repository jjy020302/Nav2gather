#!/usr/bin/env python3

import math
import statistics
from typing import Optional

import rclpy
from geometry_msgs.msg import PointStamped, PoseStamped
from nav2_simple_commander.robot_navigator import (
    BasicNavigator,
    TaskResult,
)
from rclpy.duration import Duration
from rclpy.time import Time
from tf2_ros import (
    Buffer,
    TransformException,
    TransformListener,
)


class CupGoOnce(BasicNavigator):
    """
    실제 컵의 map 좌표를 여러 번 수집한 뒤 중앙값을 계산하고,
    컵 앞 stop_distance 위치까지 한 번만 이동한다.

    입력:
      /cup/point_map

    동작:
      컵 좌표 수집
      → 중앙값 계산
      → 컵 앞 목표점 생성
      → goToPose() 1회 실행
      → 성공/실패 확인
    """

    def __init__(self) -> None:
        super().__init__(node_name='cup_go_once')

        # --------------------------------------------------
        # 사용자 설정값
        # --------------------------------------------------
        self.map_frame = 'map'
        self.robot_frame = 'base_link'

        # 컵 앞에서 멈출 거리
        self.stop_distance = 0.20

        # 목표 확정에 사용할 컵 좌표 개수
        self.required_samples = 10

        # 컵 좌표가 지나치게 흔들리면 제외하기 위한 기준
        self.maximum_sample_spread = 0.30

        # 이동 제한 시간
        self.navigation_timeout_sec = 180.0

        # --------------------------------------------------
        # 내부 상태
        # --------------------------------------------------
        self.cup_x_samples: list[float] = []
        self.cup_y_samples: list[float] = []

        self.goal_sent = False
        self.navigation_finished = False
        self.navigation_start_time = None

        # --------------------------------------------------
        # TF
        # --------------------------------------------------
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(
            self.tf_buffer,
            self,
        )

        # --------------------------------------------------
        # Subscriber
        # --------------------------------------------------
        self.cup_sub = self.create_subscription(
            PointStamped,
            '/cup/point_map',
            self.cup_callback,
            10,
        )

        # 이동 상태 확인용 타이머
        self.status_timer = self.create_timer(
            0.5,
            self.check_navigation_status,
        )

        self.get_logger().info(
            '실제 컵 좌표를 기다리는 중입니다.'
        )
        self.get_logger().info(
            f'{self.required_samples}개의 좌표를 모은 뒤 '
            f'컵 앞 {self.stop_distance:.2f} m까지 이동합니다.'
        )

    def cup_callback(
        self,
        cup_point: PointStamped,
    ) -> None:
        """
        실제 컵의 map 좌표를 수집한다.
        목표를 전송한 뒤에는 새로운 좌표를 사용하지 않는다.
        """
        if self.goal_sent or self.navigation_finished:
            return

        if cup_point.header.frame_id != self.map_frame:
            self.get_logger().warn(
                f'컵 좌표가 map 기준이 아닙니다: '
                f'{cup_point.header.frame_id}',
                throttle_duration_sec=2.0,
            )
            return

        cup_x = cup_point.point.x
        cup_y = cup_point.point.y

        if not (
            math.isfinite(cup_x)
            and math.isfinite(cup_y)
        ):
            return

        self.cup_x_samples.append(cup_x)
        self.cup_y_samples.append(cup_y)

        sample_count = len(self.cup_x_samples)

        self.get_logger().info(
            f'컵 좌표 수집 '
            f'{sample_count}/{self.required_samples}: '
            f'x={cup_x:.2f}, y={cup_y:.2f}'
        )

        if sample_count < self.required_samples:
            return

        self.prepare_and_send_goal()

    def prepare_and_send_goal(self) -> None:
        """
        수집한 좌표의 중앙값으로 컵 위치를 확정하고,
        컵 앞 정지 목표점을 계산해 Nav2에 전송한다.
        """
        if self.goal_sent:
            return

        cup_x = statistics.median(
            self.cup_x_samples
        )
        cup_y = statistics.median(
            self.cup_y_samples
        )

        # 좌표가 지나치게 흔들렸는지 확인
        x_spread = (
            max(self.cup_x_samples)
            - min(self.cup_x_samples)
        )
        y_spread = (
            max(self.cup_y_samples)
            - min(self.cup_y_samples)
        )

        spread = math.hypot(
            x_spread,
            y_spread,
        )

        if spread > self.maximum_sample_spread:
            self.get_logger().warn(
                f'컵 좌표가 너무 흔들립니다: '
                f'범위={spread:.2f} m'
            )
            self.get_logger().warn(
                '좌표를 다시 수집합니다. '
                '컵과 카메라를 움직이지 마세요.'
            )

            self.cup_x_samples.clear()
            self.cup_y_samples.clear()
            return

        robot_position = self.get_robot_position()

        if robot_position is None:
            self.get_logger().warn(
                '로봇 위치를 가져오지 못해 '
                '컵 좌표를 다시 수집합니다.'
            )
            self.cup_x_samples.clear()
            self.cup_y_samples.clear()
            return

        robot_x, robot_y = robot_position

        delta_x = cup_x - robot_x
        delta_y = cup_y - robot_y

        distance_to_cup = math.hypot(
            delta_x,
            delta_y,
        )

        if distance_to_cup <= self.stop_distance:
            self.get_logger().warn(
                f'컵이 이미 너무 가깝습니다. '
                f'현재 거리={distance_to_cup:.2f} m'
            )

            self.navigation_finished = True
            return

        # 로봇에서 컵을 향하는 단위 벡터
        unit_x = delta_x / distance_to_cup
        unit_y = delta_y / distance_to_cup

        # 컵에서 stop_distance만큼 로봇 방향으로 떨어진 위치
        goal_x = cup_x - (
            self.stop_distance * unit_x
        )
        goal_y = cup_y - (
            self.stop_distance * unit_y
        )

        # 목표점에서 컵을 바라보는 방향
        yaw = math.atan2(
            cup_y - goal_y,
            cup_x - goal_x,
        )

        goal_pose = PoseStamped()
        goal_pose.header.frame_id = self.map_frame
        goal_pose.header.stamp = (
            self.get_clock().now().to_msg()
        )

        goal_pose.pose.position.x = goal_x
        goal_pose.pose.position.y = goal_y
        goal_pose.pose.position.z = 0.0

        goal_pose.pose.orientation.x = 0.0
        goal_pose.pose.orientation.y = 0.0
        goal_pose.pose.orientation.z = math.sin(
            yaw / 2.0
        )
        goal_pose.pose.orientation.w = math.cos(
            yaw / 2.0
        )

        self.get_logger().info(
            '컵 위치를 확정했습니다.'
        )
        self.get_logger().info(
            f'로봇 위치: '
            f'x={robot_x:.2f}, y={robot_y:.2f}'
        )
        self.get_logger().info(
            f'컵 위치: '
            f'x={cup_x:.2f}, y={cup_y:.2f}'
        )
        self.get_logger().info(
            f'이동 목표: '
            f'x={goal_x:.2f}, y={goal_y:.2f}'
        )
        self.get_logger().info(
            f'현재 컵 거리={distance_to_cup:.2f} m, '
            f'정지 거리={self.stop_distance:.2f} m'
        )

        # 이 시점부터 새로운 컵 좌표는 무시한다.
        self.goal_sent = True
        self.navigation_start_time = (
            self.get_clock().now()
        )

        self.goToPose(goal_pose)

        self.get_logger().info(
            'Nav2에 실제 컵 접근 목표를 전송했습니다.'
        )

    def get_robot_position(
        self,
    ) -> Optional[tuple[float, float]]:
        """
        map 기준 현재 로봇 위치를 가져온다.
        """
        try:
            transform = self.tf_buffer.lookup_transform(
                self.map_frame,
                self.robot_frame,
                Time(),
                timeout=Duration(seconds=1.0),
            )

            return (
                transform.transform.translation.x,
                transform.transform.translation.y,
            )

        except TransformException as error:
            self.get_logger().warn(
                f'로봇 위치 TF 조회 실패: {error}',
                throttle_duration_sec=2.0,
            )
            return None

    def check_navigation_status(self) -> None:
        """
        이동 중 진행 상태와 최종 결과를 확인한다.
        """
        if not self.goal_sent:
            return

        if self.navigation_finished:
            return

        # 제한 시간 검사
        if self.navigation_start_time is not None:
            elapsed = (
                self.get_clock().now()
                - self.navigation_start_time
            ).nanoseconds / 1e9

            if elapsed > self.navigation_timeout_sec:
                self.get_logger().error(
                    '이동 제한 시간을 초과해 '
                    '현재 목표를 취소합니다.'
                )
                self.cancelTask()
                self.navigation_finished = True
                return

        if not self.isTaskComplete():
            feedback = self.getFeedback()

            if feedback is not None:
                distance_remaining = getattr(
                    feedback,
                    'distance_remaining',
                    None,
                )

                if distance_remaining is not None:
                    self.get_logger().info(
                        f'남은 거리: '
                        f'{distance_remaining:.2f} m',
                        throttle_duration_sec=2.0,
                    )

            return

        result = self.getResult()
        self.navigation_finished = True

        if result == TaskResult.SUCCEEDED:
            self.get_logger().info(
                '컵 앞 목표 위치에 도착했습니다!'
            )

        elif result == TaskResult.CANCELED:
            self.get_logger().warn(
                '컵 접근 이동이 취소되었습니다.'
            )

        elif result == TaskResult.FAILED:
            self.get_logger().error(
                '컵 접근 이동에 실패했습니다.'
            )

        else:
            self.get_logger().error(
                f'알 수 없는 이동 결과입니다: {result}'
            )


def main(args=None) -> None:
    rclpy.init(args=args)

    navigator = CupGoOnce()

    try:
        navigator.get_logger().info(
            'Nav2 활성화를 기다립니다.'
        )

        navigator.waitUntilNav2Active()

        navigator.get_logger().info(
            'Nav2가 활성화되었습니다. '
            '컵을 카메라에 보여주세요.'
        )

        rclpy.spin(navigator)

    except KeyboardInterrupt:
        navigator.get_logger().info(
            '사용자가 노드를 종료했습니다.'
        )

    finally:
        if not navigator.navigation_finished:
            navigator.cancelTask()

        navigator.destroy_node()

        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()

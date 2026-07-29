#!/usr/bin/env python3

import math
import statistics
import time
from typing import List, Optional, Tuple

import rclpy
from geometry_msgs.msg import PointStamped, PoseStamped
from nav2_simple_commander.robot_navigator import (
    BasicNavigator,
    TaskResult,
)
from rclpy.duration import Duration
from tf2_ros import (
    Buffer,
    TransformException,
    TransformListener,
)


class BottleGoMulti(BasicNavigator):
    """
    /cup/point_map 토픽으로 발행되는 보틀의 map 좌표를 받아
    보틀을 탐색하고 순서대로 이동한다.

    토픽 이름은 기존 cup_localizer와의 호환성을 위해
    /cup/point_map을 그대로 사용한다.

    동작 순서:
    1. 제자리에서 30도씩 회전하며 보틀 탐색
    2. 최대 12회 회전하여 총 360도 탐색
    3. 보틀 좌표 10개 수집
    4. 중앙값으로 좌표 안정화
    5. 보틀 앞 stop_distance 지점을 목표로 생성
    6. Nav2로 목표 지점까지 이동
    7. 도착한 보틀 좌표 저장
    8. 보틀에서 0.20m 후진
    9. 이미 방문한 보틀을 제외하고 다음 보틀 탐색
    """

    def __init__(self) -> None:
        # setup.py의 기존 실행 설정과 호환되도록
        # ROS 2 노드 이름은 cup_go_multi를 유지한다.
        super().__init__(node_name='cup_go_multi')

        # ---------------------------------------------------------
        # 사용자 설정값
        # ---------------------------------------------------------

        # 보틀 앞에서 정지할 거리
        self.stop_distance = 0.25

        # 목표 생성에 필요한 보틀 좌표 샘플 수
        self.required_samples = 10

        # 수집 좌표의 최대 퍼짐 허용값
        self.maximum_sample_spread = 0.30

        # 방문한 보틀과 새로운 보틀을 구분하는 거리
        # 방문한 보틀에서 50cm 이내면 동일한 보틀로 판단한다.
        self.visited_distance = 0.50

        # 보틀 앞으로 이동할 때 제한 시간
        self.navigation_timeout_sec = 180.0

        # 보틀 도착 후 후진하기 전 대기 시간
        self.arrival_wait_sec = 2.0

        # 보틀 도착 후 후진할 거리
        self.backup_distance = 0.20

        # 후진 속도
        self.backup_speed = 0.08

        # 후진 제한 시간
        self.backup_timeout_sec = 10.0

        # ---------------------------------------------------------
        # 보틀 탐색 회전 설정
        # ---------------------------------------------------------

        # 한 번에 회전할 각도
        self.search_step_deg = 30.0
        self.search_step_rad = math.radians(
            self.search_step_deg
        )

        # 30도씩 12회 회전하면 총 360도
        self.search_total_steps = 12

        # 한 번의 회전에 허용할 최대 시간
        self.search_step_timeout_sec = 8.0

        # 각 회전이 끝난 후 보틀 좌표를 기다릴 시간
        # 좌표 10개를 충분히 받을 수 있도록 1.5초로 설정한다.
        self.search_detection_wait_sec = 1.5

        # ---------------------------------------------------------
        # 내부 상태
        # ---------------------------------------------------------

        # SEARCHING:
        #   새로운 보틀 탐색을 시작해야 하는 상태
        #
        # ROTATING_SEARCH:
        #   제자리에서 회전하며 보틀을 찾는 상태
        #
        # GOAL_READY:
        #   안정화된 보틀 좌표가 준비된 상태
        #
        # NAVIGATING:
        #   보틀 앞으로 이동하는 상태
        #
        # BACKING_UP:
        #   보틀 도착 후 후진하는 상태
        #
        # SEARCH_FAILED:
        #   한 바퀴 동안 보틀을 찾지 못한 상태
        #
        # FAILED:
        #   회전, 이동 또는 후진이 실패한 상태
        self.state = 'SEARCHING'

        # 보틀 좌표 샘플
        self.bottle_samples: List[
            Tuple[float, float]
        ] = []

        # 이미 방문한 보틀의 map 좌표
        self.visited_bottles: List[
            Tuple[float, float]
        ] = []

        # 안정화된 보틀 좌표를 임시 저장한다.
        # 실제 이동은 main() 루프에서 실행한다.
        self.pending_bottle: Optional[
            Tuple[float, float]
        ] = None

        # ---------------------------------------------------------
        # TF 설정
        # ---------------------------------------------------------

        self.tf_buffer = Buffer()

        # main()에서 직접 spin하므로
        # 별도의 TF spin thread는 사용하지 않는다.
        self.tf_listener = TransformListener(
            self.tf_buffer,
            self,
            spin_thread=False,
        )

        # ---------------------------------------------------------
        # Subscriber
        # ---------------------------------------------------------

        # 토픽 이름은 cup_localizer와의 호환을 위해 유지한다.
        self.create_subscription(
            PointStamped,
            '/cup/point_map',
            self.bottle_callback,
            10,
        )

        self.get_logger().info(
            'Bottle Multi Navigator 시작'
        )

        self.get_logger().info(
            f'정지 거리={self.stop_distance:.2f} m, '
            f'방문 판정 거리={self.visited_distance:.2f} m, '
            f'도착 후 후진 거리='
            f'{self.backup_distance:.2f} m'
        )

        self.get_logger().info(
            f'탐색 방식={self.search_step_deg:.0f}도씩 '
            f'{self.search_total_steps}회, 총 360도'
        )

        self.get_logger().info(
            'Nav2 활성화를 기다립니다...'
        )

        self.waitUntilNav2Active()

        self.get_logger().info(
            'Nav2 활성화 완료'
        )

        self.get_logger().info(
            '첫 번째 보틀 탐색을 준비합니다.'
        )

    def bottle_callback(
        self,
        msg: PointStamped,
    ) -> None:
        """
        /cup/point_map에서 보틀의 map 좌표를 수집한다.

        SEARCHING 또는 ROTATING_SEARCH 상태에서만 좌표를 받는다.
        좌표 10개가 안정화되면 pending_bottle에 저장한다.
        """

        if self.state not in (
            'SEARCHING',
            'ROTATING_SEARCH',
        ):
            return

        bottle_x = msg.point.x
        bottle_y = msg.point.y

        # 이미 방문한 보틀 근처라면 무시한다.
        if self.is_visited_bottle(
            bottle_x,
            bottle_y,
        ):
            self.get_logger().info(
                f'이미 방문한 보틀 무시: '
                f'x={bottle_x:.2f}, '
                f'y={bottle_y:.2f}',
                throttle_duration_sec=2.0,
            )

            self.bottle_samples.clear()
            return

        self.bottle_samples.append(
            (bottle_x, bottle_y)
        )

        self.get_logger().info(
            f'보틀 좌표 수집 중: '
            f'{len(self.bottle_samples)}/'
            f'{self.required_samples}'
        )

        if (
            len(self.bottle_samples)
            < self.required_samples
        ):
            return

        stable_bottle = (
            self.calculate_stable_bottle_position()
        )

        self.bottle_samples.clear()

        if stable_bottle is None:
            self.get_logger().warning(
                '보틀 좌표가 불안정합니다. '
                '다시 측정합니다.'
            )
            return

        stable_x, stable_y = stable_bottle

        # 중앙값 계산 후 방문 여부를 다시 확인한다.
        if self.is_visited_bottle(
            stable_x,
            stable_y,
        ):
            self.get_logger().info(
                '안정화된 좌표가 이미 방문한 '
                '보틀입니다. 무시합니다.'
            )
            return

        self.pending_bottle = (
            stable_x,
            stable_y,
        )

        self.state = 'GOAL_READY'

        self.get_logger().info(
            f'이동할 보틀 좌표 준비 완료: '
            f'x={stable_x:.2f}, '
            f'y={stable_y:.2f}'
        )

    def calculate_stable_bottle_position(
        self,
    ) -> Optional[Tuple[float, float]]:
        """
        수집한 보틀 좌표의 중앙값을 계산한다.

        좌표가 maximum_sample_spread 이상 퍼져 있으면
        불안정한 검출로 판단하여 좌표를 사용하지 않는다.
        """

        if not self.bottle_samples:
            return None

        x_values = [
            sample[0]
            for sample in self.bottle_samples
        ]

        y_values = [
            sample[1]
            for sample in self.bottle_samples
        ]

        median_x = statistics.median(
            x_values
        )

        median_y = statistics.median(
            y_values
        )

        maximum_distance = max(
            math.hypot(
                x - median_x,
                y - median_y,
            )
            for x, y in self.bottle_samples
        )

        self.get_logger().info(
            f'보틀 좌표 중앙값: '
            f'x={median_x:.2f}, '
            f'y={median_y:.2f}'
        )

        self.get_logger().info(
            f'샘플 최대 퍼짐: '
            f'{maximum_distance:.2f} m'
        )

        if (
            maximum_distance
            > self.maximum_sample_spread
        ):
            return None

        return median_x, median_y

    def is_visited_bottle(
        self,
        bottle_x: float,
        bottle_y: float,
    ) -> bool:
        """
        새 보틀 좌표가 이미 방문한 보틀과 가까운지 확인한다.
        """

        for (
            visited_x,
            visited_y,
        ) in self.visited_bottles:
            distance = math.hypot(
                bottle_x - visited_x,
                bottle_y - visited_y,
            )

            if distance < self.visited_distance:
                return True

        return False

    def wait_for_bottle_detection(
        self,
        wait_sec: float,
    ) -> bool:
        """
        회전이 끝난 후 지정된 시간 동안 콜백을 처리하며
        안정화된 보틀 좌표가 들어오는지 확인한다.

        이 함수는 Nav2 action이 실행 중이지 않을 때만 호출한다.
        """

        start_time = time.monotonic()

        while (
            rclpy.ok()
            and time.monotonic() - start_time < wait_sec
        ):
            rclpy.spin_once(
                self,
                timeout_sec=0.05,
            )

            if (
                self.state == 'GOAL_READY'
                and self.pending_bottle is not None
            ):
                return True

        return False

    def search_bottle_one_rotation(self) -> bool:
        """
        보틀을 찾기 위해 제자리에서 30도씩 최대 한 바퀴 회전한다.

        반환값:
            True  : 회전 중 보틀을 발견함
            False : 한 바퀴 동안 보틀을 발견하지 못함
        """

        self.get_logger().info(
            '보틀 탐색을 시작합니다. 30도씩 최대 한 바퀴 회전합니다.'
        )

        self.state = 'ROTATING_SEARCH'

        # 이전에 들어온 검출값 제거
        self.detected_points.clear()

        search_step_rad = math.radians(30.0)
        total_steps = 12

        for step in range(total_steps):

            # 회전 전 이미 충분한 검출값이 모였다면 종료
            if len(self.detected_points) >= self.required_samples:
                self.get_logger().info(
                    '보틀 검출값이 충분히 모였습니다. 회전을 종료합니다.'
                )
                self.state = 'GOAL_READY'
                return True

            self.get_logger().info(
                f'보틀 탐색 회전: {step + 1}/{total_steps}'
            )

            # 30도 회전 명령
            self.spin(
                spin_dist=search_step_rad,
                time_allowance=10.0,
            )

            # Spin 동작이 끝날 때까지 반드시 기다림
            while not self.isTaskComplete():
                rclpy.spin_once(self, timeout_sec=0.1)

                # 회전 중에도 보틀을 충분히 찾았다면 회전 취소
                if len(self.detected_points) >= self.required_samples:
                    self.get_logger().info(
                        '회전 중 보틀을 발견했습니다. 회전을 취소합니다.'
                    )

                    self.cancelTask()

                    while not self.isTaskComplete():
                        rclpy.spin_once(self, timeout_sec=0.1)

                    self.state = 'GOAL_READY'
                    return True

            spin_result = self.getResult()

            self.get_logger().info(
                f'회전 결과: {spin_result}'
            )

            if spin_result != TaskResult.SUCCEEDED:
                self.get_logger().warn(
                    f'{step + 1}번째 회전이 완료되지 않았습니다.'
                )

            # 회전 후 카메라가 안정되고 YOLO가 검출할 시간
            wait_start = time.monotonic()

            while time.monotonic() - wait_start < 2.0:
                rclpy.spin_once(self, timeout_sec=0.1)

                if len(self.detected_points) >= self.required_samples:
                    self.get_logger().info(
                        '보틀을 발견했습니다.'
                    )
                    self.state = 'GOAL_READY'
                    return True

        self.get_logger().warn(
            '한 바퀴를 회전했지만 보틀을 찾지 못했습니다.'
        )

        self.state = 'SEARCH_FAILED'
        return False

    def get_robot_position(
        self,
    ) -> Optional[Tuple[float, float]]:
        """
        map 좌표계에서 현재 로봇 위치를 가져온다.
        """

        try:
            transform = (
                self.tf_buffer.lookup_transform(
                    'map',
                    'base_link',
                    rclpy.time.Time(),
                    timeout=Duration(
                        seconds=1.0
                    ),
                )
            )

            robot_x = (
                transform.transform.translation.x
            )

            robot_y = (
                transform.transform.translation.y
            )

            return robot_x, robot_y

        except TransformException as error:
            self.get_logger().error(
                f'로봇 위치 TF 조회 실패: '
                f'{error}'
            )
            return None

    def make_goal_pose(
        self,
        bottle_x: float,
        bottle_y: float,
    ) -> Optional[PoseStamped]:
        """
        로봇과 보틀을 잇는 선 위에서
        보틀 앞 stop_distance 지점을 Nav2 목표로 만든다.
        """

        robot_position = (
            self.get_robot_position()
        )

        if robot_position is None:
            return None

        robot_x, robot_y = robot_position

        dx = bottle_x - robot_x
        dy = bottle_y - robot_y

        distance_to_bottle = math.hypot(
            dx,
            dy,
        )

        if (
            distance_to_bottle
            <= self.stop_distance
        ):
            self.get_logger().warning(
                '보틀이 정지 거리보다 '
                '가까이 있습니다.'
            )
            return None

        unit_x = dx / distance_to_bottle
        unit_y = dy / distance_to_bottle

        # 보틀로부터 stop_distance만큼 떨어진 지점
        goal_x = (
            bottle_x
            - self.stop_distance * unit_x
        )

        goal_y = (
            bottle_y
            - self.stop_distance * unit_y
        )

        # 목표 도착 시 로봇이 보틀을 바라보도록 설정
        yaw = math.atan2(
            dy,
            dx,
        )

        goal_pose = PoseStamped()
        goal_pose.header.frame_id = 'map'
        goal_pose.header.stamp = (
            self.get_clock().now().to_msg()
        )

        goal_pose.pose.position.x = goal_x
        goal_pose.pose.position.y = goal_y
        goal_pose.pose.position.z = 0.0

        goal_pose.pose.orientation.x = 0.0
        goal_pose.pose.orientation.y = 0.0

        goal_pose.pose.orientation.z = (
            math.sin(yaw / 2.0)
        )

        goal_pose.pose.orientation.w = (
            math.cos(yaw / 2.0)
        )

        self.get_logger().info(
            f'현재 로봇: '
            f'x={robot_x:.2f}, '
            f'y={robot_y:.2f}'
        )

        self.get_logger().info(
            f'검출된 보틀: '
            f'x={bottle_x:.2f}, '
            f'y={bottle_y:.2f}'
        )

        self.get_logger().info(
            f'이동 목표: '
            f'x={goal_x:.2f}, '
            f'y={goal_y:.2f}'
        )

        self.get_logger().info(
            f'보틀과 목표 지점 사이 거리: '
            f'{self.stop_distance:.2f} m'
        )

        return goal_pose

    def backup_after_arrival(
        self,
    ) -> bool:
        """
        보틀 앞 목표 지점에 도착한 뒤
        설정된 거리만큼 후진한다.
        """

        self.state = 'BACKING_UP'

        self.get_logger().info(
            f'보틀 도착 완료. '
            f'{self.backup_distance:.2f} m '
            f'후진을 시작합니다.'
        )

        self.backup(
            backup_dist=self.backup_distance,
            backup_speed=self.backup_speed,
            time_allowance=self.backup_timeout_sec,
        )

        start_time = time.monotonic()

        while not self.isTaskComplete():
            elapsed_time = (
                time.monotonic()
                - start_time
            )

            if (
                elapsed_time
                > self.backup_timeout_sec
            ):
                self.get_logger().error(
                    '후진 제한 시간을 '
                    '초과했습니다.'
                )

                self.cancelTask()
                return False

            time.sleep(0.1)

        result = self.getResult()

        if result == TaskResult.SUCCEEDED:
            self.get_logger().info(
                f'{self.backup_distance:.2f} m '
                f'후진 완료'
            )
            return True

        if result == TaskResult.CANCELED:
            self.get_logger().warning(
                '후진이 취소되었습니다.'
            )
            return False

        if result == TaskResult.FAILED:
            self.get_logger().error(
                '후진하지 못했습니다.'
            )
            return False

        self.get_logger().error(
            f'알 수 없는 후진 결과: '
            f'{result}'
        )
        return False

    def navigate_to_bottle(
        self,
        bottle_x: float,
        bottle_y: float,
    ) -> None:
        """
        보틀 앞 목표를 생성하여 Nav2에 전달하고
        이동 결과를 처리한다.
        """

        self.state = 'NAVIGATING'

        goal_pose = self.make_goal_pose(
            bottle_x,
            bottle_y,
        )

        if goal_pose is None:
            self.get_logger().warning(
                '목표 생성 실패. '
                '다시 보틀을 탐색합니다.'
            )

            self.pending_bottle = None
            self.bottle_samples.clear()
            self.state = 'SEARCHING'
            return

        self.get_logger().info(
            '보틀 앞으로 이동을 시작합니다.'
        )

        self.goToPose(goal_pose)

        start_time = time.monotonic()

        while not self.isTaskComplete():
            feedback = self.getFeedback()

            if feedback is not None:
                remaining_distance = (
                    feedback.distance_remaining
                )

                self.get_logger().info(
                    f'남은 거리: '
                    f'{remaining_distance:.2f} m',
                    throttle_duration_sec=1.0,
                )

            elapsed_time = (
                time.monotonic()
                - start_time
            )

            if (
                elapsed_time
                > self.navigation_timeout_sec
            ):
                self.get_logger().error(
                    '이동 제한 시간을 '
                    '초과했습니다.'
                )

                self.cancelTask()

                self.pending_bottle = None
                self.bottle_samples.clear()
                self.state = 'FAILED'
                return

            time.sleep(0.1)

        result = self.getResult()

        if result == TaskResult.SUCCEEDED:
            self.get_logger().info(
                '보틀 앞 목표 지점에 '
                '도착했습니다!'
            )

            # 실제 보틀 좌표를 방문 목록에 저장한다.
            self.visited_bottles.append(
                (bottle_x, bottle_y)
            )

            self.get_logger().info(
                f'방문한 보틀 개수: '
                f'{len(self.visited_bottles)}'
            )

            for (
                index,
                (
                    visited_x,
                    visited_y,
                ),
            ) in enumerate(
                self.visited_bottles,
                start=1,
            ):
                self.get_logger().info(
                    f'방문 보틀 {index}: '
                    f'x={visited_x:.2f}, '
                    f'y={visited_y:.2f}'
                )

            # 보틀 앞에서 잠시 대기한다.
            time.sleep(
                self.arrival_wait_sec
            )

            backup_succeeded = (
                self.backup_after_arrival()
            )

            if backup_succeeded:
                self.get_logger().info(
                    '후진 완료. '
                    '다음 보틀 탐색을 준비합니다.'
                )
            else:
                self.get_logger().warning(
                    '후진은 완료되지 않았지만 '
                    '다음 보틀 탐색을 계속합니다.'
                )

            self.pending_bottle = None
            self.bottle_samples.clear()
            self.state = 'SEARCHING'

            self.get_logger().info(
                '도착한 보틀을 제외하고 '
                '다음 보틀을 탐색합니다.'
            )

        elif result == TaskResult.CANCELED:
            self.get_logger().warning(
                '보틀 이동이 취소되었습니다.'
            )

            self.pending_bottle = None
            self.bottle_samples.clear()
            self.state = 'FAILED'

        elif result == TaskResult.FAILED:
            self.get_logger().error(
                '보틀로 이동하지 못했습니다.'
            )

            self.pending_bottle = None
            self.bottle_samples.clear()
            self.state = 'FAILED'

        else:
            self.get_logger().error(
                f'알 수 없는 이동 결과: '
                f'{result}'
            )

            self.pending_bottle = None
            self.bottle_samples.clear()
            self.state = 'FAILED'


def main(args=None) -> None:
    rclpy.init(args=args)

    navigator = BottleGoMulti()

    try:
        while rclpy.ok():
            # SEARCHING 상태가 되면
            # 보틀을 찾기 위해 최대 한 바퀴 회전한다.
            if navigator.state == 'SEARCHING':
                navigator.search_bottle_one_rotation()
                continue

            # Action이 실행 중이지 않을 때
            # subscriber와 TF 콜백을 처리한다.
            rclpy.spin_once(
                navigator,
                timeout_sec=0.1,
            )

            # 안정화된 보틀 좌표가 준비되면 이동한다.
            if (
                navigator.state == 'GOAL_READY'
                and navigator.pending_bottle
                is not None
            ):
                (
                    bottle_x,
                    bottle_y,
                ) = navigator.pending_bottle

                navigator.navigate_to_bottle(
                    bottle_x,
                    bottle_y,
                )

            # 한 바퀴 동안 새로운 보틀을 찾지 못하면
            # 로봇을 정지한 상태로 유지한다.
            if (
                navigator.state
                == 'SEARCH_FAILED'
            ):
                navigator.get_logger().warning(
                    '한 바퀴 탐색이 끝났지만 '
                    '새로운 보틀을 찾지 못했습니다. '
                    '노드를 종료합니다.'
                )
                break

            if navigator.state == 'FAILED':
                navigator.get_logger().error(
                    '동작 실패로 노드를 종료합니다.'
                )
                break

    except KeyboardInterrupt:
        navigator.get_logger().info(
            'Bottle Multi Navigator 종료'
        )

    finally:
        navigator.destroyNode()

        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()

#!/usr/bin/env python3

import rclpy

from geometry_msgs.msg import PoseStamped
from nav2_simple_commander.robot_navigator import BasicNavigator, TaskResult


def main():
    rclpy.init()

    navigator = BasicNavigator()

    # Navigation2와 AMCL은 이미 별도로 실행하고,
    # RViz의 2D Pose Estimate로 초기 위치를 설정한 상태에서 사용한다.
    # waitUntilNav2Active()는 초기 위치를 다시 발행할 수 있으므로 사용하지 않는다.

    goal_pose = PoseStamped()
    goal_pose.header.frame_id = 'map'
    goal_pose.header.stamp = navigator.get_clock().now().to_msg()

    # RViz의 Publish Point에서 확인한 목적지
    goal_pose.pose.position.x = 0.9
    goal_pose.pose.position.y = -3.0
    goal_pose.pose.position.z = 0.0

    # 목표 도착 시 바라볼 방향
    goal_pose.pose.orientation.x = 0.0
    goal_pose.pose.orientation.y = 0.0
    goal_pose.pose.orientation.z = 0.0
    goal_pose.pose.orientation.w = 1.0

    navigator.get_logger().info(
        f'목적지 전송: '
        f'x={goal_pose.pose.position.x:.2f}, '
        f'y={goal_pose.pose.position.y:.2f}'
    )

    navigator.goToPose(goal_pose)

    feedback_count = 0

    while not navigator.isTaskComplete():
        feedback = navigator.getFeedback()

        if feedback is not None:
            feedback_count += 1

            if feedback_count % 10 == 0:
                navigator.get_logger().info(
                    f'남은 거리: {feedback.distance_remaining:.2f} m'
                )

    result = navigator.getResult()

    if result == TaskResult.SUCCEEDED:
        navigator.get_logger().info('목적지 도착 성공!')

    elif result == TaskResult.CANCELED:
        navigator.get_logger().warn('목적지 이동이 취소되었습니다.')

    elif result == TaskResult.FAILED:
        navigator.get_logger().error('목적지 이동에 실패했습니다.')

    else:
        navigator.get_logger().error(
            f'알 수 없는 Navigation 결과입니다: {result}'
        )

    navigator.destroyNode()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

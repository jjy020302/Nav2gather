#!/usr/bin/env python3

import rclpy

from geometry_msgs.msg import PoseStamped
from nav2_simple_commander.robot_navigator import BasicNavigator, TaskResult


def create_pose(navigator, x, y, z=0.0, w=1.0):
    pose = PoseStamped()
    pose.header.frame_id = 'map'
    pose.header.stamp = navigator.get_clock().now().to_msg()

    pose.pose.position.x = x
    pose.pose.position.y = y
    pose.pose.position.z = 0.0

    pose.pose.orientation.x = 0.0
    pose.pose.orientation.y = 0.0
    pose.pose.orientation.z = z
    pose.pose.orientation.w = w

    return pose


def main():
    rclpy.init()

    navigator = BasicNavigator()

    waypoint_1 = create_pose(
        navigator,
        x=0.9,
        y=-3.0
    )

    waypoint_2 = create_pose(
        navigator,
        x=0.5,
        y=-2.5
    )

    waypoints = [
        waypoint_1,
        waypoint_2
    ]

    navigator.get_logger().info(
        f'{len(waypoints)}개의 Waypoint 이동을 시작합니다.'
    )

    navigator.followWaypoints(waypoints)

    feedback_count = 0

    while not navigator.isTaskComplete():
        feedback = navigator.getFeedback()

        if feedback is not None:
            feedback_count += 1

            if feedback_count % 10 == 0:
                current_waypoint = getattr(
                    feedback,
                    'current_waypoint',
                    -1
                )

                navigator.get_logger().info(
                    f'현재 Waypoint 번호: {current_waypoint}'
                )

    result = navigator.getResult()

    if result == TaskResult.SUCCEEDED:
        navigator.get_logger().info(
            '모든 Waypoint 이동 성공!'
        )

    elif result == TaskResult.CANCELED:
        navigator.get_logger().warn(
            'Waypoint 이동이 취소되었습니다.'
        )

    elif result == TaskResult.FAILED:
        navigator.get_logger().error(
            'Waypoint 이동에 실패했습니다.'
        )

    else:
        navigator.get_logger().error(
            f'알 수 없는 결과입니다: {result}'
        )

    navigator.destroyNode()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

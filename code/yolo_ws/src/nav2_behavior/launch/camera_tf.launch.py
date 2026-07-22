#!/usr/bin/env python3

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        # ---------------------------------------------------------
        # base_link -> camera_link
        #
        # 실제 카메라 장착 위치
        # x: 로봇 중심에서 앞쪽 10 cm
        # y: 로봇 중심에서 좌우 0 cm
        # z: 로봇 중심에서 위쪽 12 cm
        # ---------------------------------------------------------
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='base_to_camera_tf',
            output='screen',
            arguments=[
                '--x', '0.10',
                '--y', '0.00',
                '--z', '0.12',
                '--roll', '0.0',
                '--pitch', '0.0',
                '--yaw', '0.0',
                '--frame-id', 'base_link',
                '--child-frame-id', 'camera_link',
            ],
        ),

        # ---------------------------------------------------------
        # camera_link -> camera_optical_frame
        #
        # 카메라 일반 좌표축을 optical 좌표축으로 변환
        # optical frame:
        #   x: 화면 오른쪽
        #   y: 화면 아래
        #   z: 카메라 정면
        # ---------------------------------------------------------
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='camera_to_optical_tf',
            output='screen',
            arguments=[
                '--x', '0.0',
                '--y', '0.0',
                '--z', '0.0',
                '--roll', '-1.5708',
                '--pitch', '0.0',
                '--yaw', '-1.5708',
                '--frame-id', 'camera_link',
                '--child-frame-id', 'camera_optical_frame',
            ],
        ),

        # ---------------------------------------------------------
        # 컵 3D 위치 추정 노드
        # ---------------------------------------------------------
        Node(
            package='nav2_behavior',
            executable='cup_localizer',
            name='cup_localizer',
            output='screen',
        ),
    ])

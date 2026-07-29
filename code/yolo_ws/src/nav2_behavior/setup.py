import os
from glob import glob
from setuptools import find_packages, setup

package_name = 'nav2_behavior'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'),
            glob('launch/*.launch.py')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='csilab',
    maintainer_email='csilab@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
	    'go_to_pose = nav2_behavior.go_to_pose:main',
	    'follow_waypoints = nav2_behavior.follow_waypoints:main',
            'yolo_reaction = nav2_behavior.yolo_reaction:main',
            'bottle_nav = nav2_behavior.bottle_nav:main',
            'cup_localizer = nav2_behavior.cup_localizer:main',
            'cup_go_once = nav2_behavior.cup_go_once:main',
            'cup_go_multi = nav2_behavior.cup_go_multi:main',
            'bottle_behavior = nav2_behavior.bottle_behavior:main',
        ],
    },
)


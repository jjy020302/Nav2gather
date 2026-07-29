from setuptools import find_packages
from setuptools import setup

setup(
    name='frontier_exploration_ros2',
    version='1.6.1',
    packages=find_packages(
        include=('frontier_exploration_ros2', 'frontier_exploration_ros2.*')),
)

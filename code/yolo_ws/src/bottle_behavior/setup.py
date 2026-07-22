from setuptools import find_packages, setup

package_name = 'bottle_behavior'

setup(
    name=package_name,
    version='0.0.1',
    packages=find_packages(exclude=['test']),
    data_files=[
        (
            'share/ament_index/resource_index/packages',
            ['resource/' + package_name],
        ),
        (
            'share/' + package_name,
            ['package.xml'],
        ),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='csilab',
    maintainer_email='csilab@example.com',
    description='Simple bottle detection behavior for TurtleBot3',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'bottle_stop = bottle_behavior.bottle_stop:main',
        ],
    },
)

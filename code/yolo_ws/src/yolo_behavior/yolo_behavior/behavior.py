#!/usr/bin/env python3

import rclpy
from rclpy.node import Node

from geometry_msgs.msg import Twist
from vision_msgs.msg import Detection2DArray


class BottleStop(Node):

    def __init__(self):
        super().__init__('bottle_stop')

        self.sub = self.create_subscription(
            Detection2DArray,
            '/yolo/detections',
            self.callback,
            10)

        self.pub = self.create_publisher(
            Twist,
            '/cmd_vel',
            10)

        self.stop = Twist()

    def callback(self, msg):

        bottle_found = False

        for detection in msg.detections:

            for result in detection.results:

                if result.hypothesis.class_id == "bottle":
                    bottle_found = True

        if bottle_found:
            self.get_logger().info("Bottle detected! Stop.")

            self.pub.publish(self.stop)


def main():

    rclpy.init()

    node = BottleStop()

    rclpy.spin(node)

    node.destroy_node()

    rclpy.shutdown()


if __name__ == '__main__':
    main()

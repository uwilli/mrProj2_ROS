#!/usr/bin/env python3
 
"""
Publishes Twist messages to /cmd_vel, taking joystick input from spacemouse, a 3d-Cad mouse.

Adapted to Spacemouse from publisher for xbox controller which was from Yannik Martin.

Author: Urban Willi
"""

######################################################################################################
# Imports
######################################################################################################
import rospy
import roslib
from geometry_msgs.msg import Twist

######################################################################################################
# Functions
######################################################################################################

def publisherController():
    controllerpub = rospy.Publisher('cmd_vel', Twist, queue_size=1)
    rospy.init_node('spacemouse_controller_node', anonymous=True)
    rate = rospy.Rate(10) # Hz

    speed=0
    steering=0
    
    while not rospy.is_shutdown():
        
        # Algorithm
        
        inputcontroller_msg = Twist()
        inputcontroller_msg.linear.x = speed # speed
        inputcontroller_msg.angular.z = steering # direction


        rospy.loginfo(inputcontroller_msg)
        controllerpub.publish(inputcontroller_msg)

        rate.sleep()


######################################################################################################
# Main
######################################################################################################

if __name__ == '__main__':
    try:
        publisherController()
    except rospy.ROSInterruptException:
        pass
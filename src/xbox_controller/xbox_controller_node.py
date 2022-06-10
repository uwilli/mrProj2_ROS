#!/usr/bin/env python3
 
""" Code from Kevin Peter"""

from re import X
import rospy
import roslib
from geometry_msgs.msg import Twist
import time
import curses
import atexit
import pigpio
import struct

def publisherController():
    controllerpub = rospy.Publisher('cmd_vel', Twist, queue_size=1)
    rospy.init_node('xbox_controller_node', anonymous=True)
    rate = rospy.Rate(10) # Hz

    xbox_file_path = "/dev/input/js0"
    INPUTSIZE = struct.calcsize("LhBB")
    file = open(xbox_file_path, "rb")
    event = file.read(INPUTSIZE)
    
    speed=0
    steering=0
    reverse=0
    
    while not rospy.is_shutdown():
        (tv_msec, value, cont_type, number) = struct.unpack("LhBB", event)
        #print(value)
        
        if cont_type == 2: # Joystick
        	if number == 4:
        		value = value + 32767
        		speed = value / 65534
        	elif number == 0: # links/rechts
        		steering=value/-32767
        if cont_type == 1: # Button
        	if number == 0: # A
        		if value == 1:
        			reverse = 1
        		else
        			reverse = 0

        inputcontroller_msg = Twist()
        inputcontroller_msg.linear.x = reverse*speed # speed
        inputcontroller_msg.angular.z = steering # direction


        rospy.loginfo(inputcontroller_msg)
        controllerpub.publish(inputcontroller_msg)

        event = file.read(INPUTSIZE)

        rate.sleep()

if __name__ == '__main__':
    try:
        publisherController()
    except rospy.ROSInterruptException:
        pass

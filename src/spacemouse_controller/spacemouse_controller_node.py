#!/usr/bin/env python3

"""
Publishes Twist messages to /cmd_vel, taking joystick input from spacemouse, a 3d-Cad mouse.

Adapted to Spacemouse from publisher for xbox controller which was from Yannik Martin.

Author: Urban Willi
"""

######################################################################################################
# Imports
######################################################################################################
# Ros
import rospy
import roslib
from geometry_msgs.msg import Twist

# Usb
import usb.core
import usb.util

######################################################################################################
# Spacemouse class
######################################################################################################

"""
This script reads the data from the 3d connexion Spacemouse Pro Wireless and prints them to the console.
Currently only single button presses are considered. The information available would allow concurrent and nested pushes
to be recognized.

Sources used:
From jwick1234, github. Link: https://github.com/uwilli/3d-mouse-rpi-python/blob/develop/HelloSpaceNavigator.py
From johnhw, github. Space Mouse Wireless Windows: https://github.com/johnhw/pyspacenavigator/blob/master/spacenavigator.py

Changed and blended and marinated by Urban Willi
"""
class Spacemouse:
    def __init__(self):
        ## Instance variables
        self.x = None
        self.y = None
        self.z = None
        self.roll = None
        self.pitch = None
        self.yaw = None

        self.escape = None
        self.b1 = None
        self.b2 = None
        self.b3 = None
        self.b4 = None
        self.lockRotation = None

        self.dev = None

        ## Init
        # Look for Space Mouse
        self.dev = usb.core.find(idVendor=0x256f, idProduct=0xc652)  # use usbFindVendorProductID.py
        if self.dev is None:
            raise ValueError('Spacemouse not found');
        else:
            print('Spacemouse Pro Wireless found')

        # dev.set_configuration() # Apparently automatically chosen config, as this throws an error.

        # Deal with Error resource-busy
        if self.dev.is_kernel_driver_active(0):
            try:
                self.dev.detach_kernel_driver(0)
            except usb.core.USBError as e:
                sys.exit("Could not detach kernel driver from interface 0")

    def __del__(self):
        usb.util.dispose_resources(self.dev)  # free usb device

    # Spacemouse talks via receiver over Usb, using interrupt msgs.
    # Timeout for waiting on interrupt, in s. (Milliseconds recommended).
    # Single button presses and following release recognized. Simultaneous several buttons not yet supported.
    def getInterruptMsg(self):
        usbInt = self.dev.read(0x81, 0x20, 10)  # endpoint address, msg length -> wMaxPacketSize, timeout (optional, device default if not set)

        msgType = usbInt[0]

        released = True  # if buttons released/Joystick not touched, msg is all zeros except msg type
        for item in usbInt[1:]:
            if item != 0:
                released = False
                break

        if msgType == 1:  # Joystick
            if released:
                self.x = None
                self.y = None
                self.z = None
                self.roll = None
                self.pitch = None
                self.yaw = None
                print('Joystick released')
                return

            #print('Joystick')

            self.x = self.__to_int16(self.__tryIndexAbsVal(usbInt, 1), self.__tryIndexAbsVal(usbInt, 2))
            self.y = -1 * self.__to_int16(self.__tryIndexAbsVal(usbInt, 3), self.__tryIndexAbsVal(usbInt, 4))
            self.z = -1 * self.__to_int16(self.__tryIndexAbsVal(usbInt, 5), self.__tryIndexAbsVal(usbInt, 6))
            self.pitch = -1 * self.__to_int16(self.__tryIndexAbsVal(usbInt, 7), self.__tryIndexAbsVal(usbInt, 8))
            self.roll = -1 * self.__to_int16(self.__tryIndexAbsVal(usbInt, 9), self.__tryIndexAbsVal(usbInt, 10))
            self.yaw = -1 * self.__to_int16(self.__tryIndexAbsVal(usbInt, 11), self.__tryIndexAbsVal(usbInt, 12))

            # print('x     : ', self.x)
            # print('y     : ', self.y)
            # print('z     : ', self.z)
            # print('pitch  : ', self.pitch)
            # print('roll : ', self.roll)
            # print('yaw   : ', self.yaw)

        elif msgType == 3:
            if released:
                self.escape = None
                self.b1 = None
                self.b2 = None
                self.b3 = None
                self.b4 = None
                self.lockRotation = None
                print('Button released')
                return
            # print('Button')

            # Position 1
            val = self.__tryIndexAbsVal(usbInt, 1)
            if val == 1:
                print('Menu')
            elif val == 2:
                print('Fit')
            elif val == 4:
                print('Top')
            elif val == 16:
                print('Right')
            elif val == 32:
                print('Front')

            # Position 2
            val = self.__tryIndexAbsVal(usbInt, 2)
            if val == 1:
                print('Roll View')
            elif val == 16:
                self.b1 = True
                # print('B1')
            elif val == 32:
                self.b2 = True
                # print('B2')
            elif val == 64:
                self.b3 = True
                # print('B3')
            elif val == 128:
                self.b4 = True
                # print('B4')

            # Position 3
            val = self.__tryIndexAbsVal(usbInt, 3)
            if val == -1:  # out of range
                return

            if val == 64:
                # print('Escape')
                self.escape = True
            elif val == 128:
                print('Alt')

            # Position 4
            val = self.__tryIndexAbsVal(usbInt, 4)
            if val == -1:  # out of range
                return

            if val == 1:
                print('Shift')
            elif val == 2:
                print('Ctrl')
            elif val == 4:
                self.lockRotation = True
                # print('Lock Rotation')

        elif msgType == 23:
            # print('inactivity?')
            pass
        else:
            print('unknown')

        # enumerate
        # for i, item in enumerate(usbInt):
        #     print(item)

    # returns None if index out of range
    def __tryIndexTwosComp(self, list, index):
        ret = None
        try:
            absVal = list[index]
        except ValueError:
            return ret

        if absVal > 127:  # two's complement
            ret = ~absVal & 1
        else:
            ret = absVal
        return ret

    # returns -1 if index out of range
    def __tryIndexAbsVal(self, list, index):
        try:
            ret = list[index]
        except ValueError:
            return -1
        return ret

    # convert two 8 bit bytes to a signed 16 bit integer
    # from johnhw
    def __to_int16(self, y1, y2):
        x = (y1) | (y2 << 8)
        if x >= 32768:
            x = -(65536 - x)
        return x


######################################################################################################
# Functions
######################################################################################################

# Ros publisher
def publisherController():
    controllerpub = rospy.Publisher('cmd_vel', Twist, queue_size=1)
    rospy.init_node('spacemouse_controller_node', anonymous=True)
    rate = rospy.Rate(100)  # Hz

    inputcontroller_msg = Twist()

    controller = Spacemouse()

    released = True
    constSpeed = False
    active = 0
    while not rospy.is_shutdown():
        active = 0

        try:
            controller.getInterruptMsg()

        except usb.core.USBError as er:
            if er.errno == 110:  # Timeout
                pass

        if controller.lockRotation == None:
            released = True

        if controller.lockRotation:
            if released:
                rospy.logdebug("Lock rotation pushed")
                constSpeed = not constSpeed
                rospy.logdebug("Toggled speed control, now is set to: " + str(constSpeed))
                released = False

                if controller.pitch == None:
                    speed = 0
                else:
                    speed = controller.pitch / 350 # speed
                inputcontroller_msg.linear.x = speed

        if (controller.pitch and not constSpeed):
            active = 1
            inputcontroller_msg.linear.x = controller.pitch / 350  # speed
        if controller.yaw:
            active = 1
            inputcontroller_msg.angular.z = controller.yaw / 350  # direction

        # rospy.loginfo(inputcontroller_msg) # prints on rosinfo
        if active:
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

#include <ros/ros.h>
#include "mrcar_hardware_ctrl/SteeringServo.hpp"


int main(int argc, char** argv)
{
	ros::init(argc, argv, "mrcar_hardware_ctrl");
	ros::NodeHandle nodeHandle("~");

	steering_servo::SteeringServo steeringServo(nodeHandle);

	ros::spin();
	return 0;
}


#include <ros/ros.h>
#include "mrcar_hardware_ctrl/SteeringServo.hpp"


int main(int argc, char** argv)
{
	ros::init(argc, argv, "steering_servo");
	ros::NodeHandle nodeHandle("~");

	mrcar_hardware_ctrl::SteeringServo steeringServo(nodeHandle);

	ros::spin();
	return 0;
}


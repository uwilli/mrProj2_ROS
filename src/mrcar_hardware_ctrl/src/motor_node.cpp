#include <ros/ros.h>
#include "mrcar_hardware_ctrl/Motor.hpp"


int main(int argc, char** argv)
{
	ros::init(argc, argv, "motor");
	ros::NodeHandle nodeHandle("~");

	motor::Motor motor(nodeHandle);

	ros::spin();
	return 0;
}


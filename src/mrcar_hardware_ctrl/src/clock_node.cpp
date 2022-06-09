#include <ros/ros.h>
#include "mrcar_hardware_ctrl/Clock.hpp"


int main(int argc, char** argv)
{
	ros::init(argc, argv, "motor");
	ros::NodeHandle nodeHandle("~");

	mrcar_hardware_ctrl::Clock motor(nodeHandle);

	ros::spin();
	return 0;
}


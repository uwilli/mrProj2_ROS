#include <ros/ros.h>
#include "mrcar_hardware_ctrl/XboxController.hpp"


int main(int argc, char** argv)
{
	ros::init(argc, argv, "clock");
	ros::NodeHandle nodeHandle("~");

	mrcar_hardware_ctrl::XboxController xbox(nodeHandle);

	ros::Timer publishXbox = nodeHandle.createTimer(ros::Duration(xbox.getPeriod()), std::bind(&mrcar_hardware_ctrl::XboxController::publish, xbox));

	ros::spin();
	return 0;
}


#include <ros/ros.h>
#include "mrcar_hardware_ctrl/Clock.hpp"


int main(int argc, char** argv)
{
	ros::init(argc, argv, "clock");
	ros::NodeHandle nodeHandle("~");

	mrcar_hardware_ctrl::Clock clock(nodeHandle);

	ros::Timer publishTime = nodeHandle.createTimer(ros::Duration(clock.getPeriod()), std::bind(&mrcar_hardware_ctrl::Clock::publishTime, clock));

	ros::spin();
	return 0;
}


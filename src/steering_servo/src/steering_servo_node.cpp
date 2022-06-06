#include <ros/ros.h>
#include "steering_servo/SteeringServo.hpp"

int main(int argc, char** argv)
{
	ros::init(argc, argv, "steering_servo");
	ros::NodeHandle nodeHandle("~");

	steering_servo::SteeringServo steeringServo(nodeHandle);

	ros::spin();
	return 0;
}

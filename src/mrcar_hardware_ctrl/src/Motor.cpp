#include "mrcar_hardware_ctrl/Motor.hpp"

namespace motor
{


Motor::Motor(ros::NodeHandle& nodeHandle) : nodeHandle_(nodeHandle), m3_(3) // this is called an initializer list
				{
	if (!readParameters_())
	{
		ROS_ERROR("Could not read parameters.");
		ros::requestShutdown();
	}

	subscriber_ = nodeHandle_.subscribe(subscriberTopic_, 1,
			&Motor::topicCallback_, this);

	ROS_INFO("Successfully launched motor node.");
				}


bool Motor::readParameters_()
{
	if (!nodeHandle_.getParam("motor/subscriber_topic", subscriberTopic_)) return false;
	return true;
}


void Motor::topicCallback_(const geometry_msgs::Twist& msg)
{
	int percent = msg.linear.x * 100;

	m3_.speed(percent);
}

} /* namespace motor */


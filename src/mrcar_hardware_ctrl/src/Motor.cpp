#include "mrcar_hardware_ctrl/Motor.hpp"

namespace mrcar_hardware_ctrl
{


Motor::Motor(ros::NodeHandle& nodeHandle) : nodeHandle_(nodeHandle), m3_(3) // this is called an initializer list
{
	if (!readParameters_())
	{
		ROS_ERROR("Could not read parameters.");
		ros::requestShutdown();
	}

	check_namespace_topic_(subscriberTopic_);
	check_namespace_topic_(clock_subscriberTopic_);

	subscriber_ = nodeHandle_.subscribe(subscriberTopic_, 1, &Motor::topicCallback_, this);
	subscriber_ = nodeHandle_.subscribe(clock_subscriberTopic_, 1, &Motor::clock_topicCallback_, this);

	// Calculate max delay (2 clock cycles)
	max_duration_no_msg_ = ros::Duration(2.0 / float(clock_Hz_));

	ROS_DEBUG_STREAM("Subscriber topic Motor: " << subscriberTopic_);
	ROS_INFO("Successfully launched motor node.");
}


bool Motor::readParameters_()
{
	if (!nodeHandle_.getParam("motor/subscriber_topic", subscriberTopic_)) return false;
	if (!nodeHandle_.getParam("clock/publisher_topic", clock_subscriberTopic_)) return false;
	if (!nodeHandle_.getParam("clock/publisher_Hz", clock_Hz_)) return false;
	return true;
}


void Motor::topicCallback_(const geometry_msgs::Twist& msg)
{
	int percent = msg.linear.x * 100;

	ROS_DEBUG_STREAM("Motor speed written: " << percent);

	m3_.speed(percent);
}


void Motor::clock_topicCallback_(const std_msgs::Time& msg)
{
	if((msg.data - time_last_msg_.data) > max_duration_no_msg_)
	{
		m3_.speed(0);
	}

	time_last_msg_ = msg;
}


void Motor::check_namespace_topic_(const std::string& subTopic)
{
	// Build correct namespace for topic
	if(subTopic.empty())
	{
		ROS_ERROR("Empty subscriber topic in param server");
		ros::requestShutdown();
	}
	if(subTopic.front() != '/'){
		subTopic = "/" + subTopic;
	}

	//subTopic = "/mrcar_hardware_ctrl" + subTopic;
}

} /* namespace mrcar_hardware_ctrl */


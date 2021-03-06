#include "mrcar_hardware_ctrl/Clock.hpp"

namespace mrcar_hardware_ctrl
{


Clock::Clock(ros::NodeHandle& nodeHandle) : nodeHandle_(nodeHandle) // this is called an initializer list
{
	if (!readParameters_())
	{
		ROS_ERROR("Could not read parameters.");
		ros::requestShutdown();
	}

	// Build correct namespace for topic
	if(publisherTopic_.empty())
	{
		ROS_ERROR("Empty publisher topic for clock in param server");
		ros::requestShutdown();
	}
	if(publisherTopic_.front() != '/')
	{
		publisherTopic_.insert(0, 1, '/');
	}

	//publisherTopic_ = "/mrcar_hardware_ctrl" + publisherTopic_;

	publisher_ = nodeHandle_.advertise<std_msgs::Time>(publisherTopic_, 1); // message_queue = 1

	ROS_DEBUG_STREAM("Publisher topic Clock: " << publisherTopic_);
	ROS_INFO("Successfully launched clock node.");
}


void Clock::publishTime()
{
	std_msgs::Time current_time;
	current_time.data = ros::Time::now();
	publisher_.publish(current_time);
}


float Clock::getPeriod()
{
	return 1.0 / float(publisher_Hz_);
}


int Clock::getHz()
{
	return publisher_Hz_;
}


bool Clock::readParameters_()
{
	if (!nodeHandle_.getParam("clock/publisher_topic", publisherTopic_)) return false;
	if (!nodeHandle_.getParam("clock/publisher_Hz", publisher_Hz_)) return false;
	return true;
}


} /* namespace mrcar_hardware_ctrl */


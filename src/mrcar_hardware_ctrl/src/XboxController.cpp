#include "mrcar_hardware_ctrl/XboxController.hpp"

namespace mrcar_hardware_ctrl
{


XboxController::XboxController(ros::NodeHandle& nodeHandle) : nodeHandle_(nodeHandle) // this is called an initializer list
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

	publisher_ = nodeHandle_.advertise<geometry_msgs::Twist>(publisherTopic_, 1); // message_queue = 1

	ROS_DEBUG_STREAM("Publisher topic Xbox: " << publisherTopic_);
	ROS_INFO("Successfully launched Xbox node.");
}


void XboxController::publish()
{
	// TODO
}


float XboxController::getPeriod()
{
	return 1.0 / float(publisher_Hz_);
}


bool XboxController::readParameters_()
{
	if (!nodeHandle_.getParam("xbox/publisher_topic", publisherTopic_)) return false;
	if (!nodeHandle_.getParam("clock/publisher_Hz", publisher_Hz_)) return false;
	return true;
}


} /* namespace mrcar_hardware_ctrl */


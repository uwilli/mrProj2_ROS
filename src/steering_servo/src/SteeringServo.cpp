#include "steering_servo/SteeringServo.hpp"

namespace steering_servo
{

SteeringServo::SteeringServo(const ros::NodeHandle& nodeHandle) : nodeHandle_(nodeHandle)
{
	if (!readParameters_())
	{
	    ROS_ERROR("Could not read parameters.");
	    ros::requestShutdown();
	}

	subscriber_ = nodeHandle_.subscribe(subscriberTopic_, 1,
	                                      &SteeringServo::topicCallback_, this);

	ROS_INFO("Successfully launched steering_servo node.");
}


bool SteeringServo::readParameters_()
{
  if (!nodeHandle_.getParam("subscriber_topic", subscriberTopic_)) return false;
  return true;
}


void SteeringServo::topicCallback_()
{
  // TODO
}

} /* namespace steering_servo */

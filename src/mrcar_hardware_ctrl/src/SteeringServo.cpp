#include "mrcar_hardware_ctrl/SteeringServo.hpp"

namespace steering_servo
{


SteeringServo::SteeringServo(ros::NodeHandle& nodeHandle) : nodeHandle_(nodeHandle), servo_(13, true) // this is called an initializer list
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
	if (!nodeHandle_.getParam("steering_servo/subscriber_topic", subscriberTopic_)) return false;
	if (!nodeHandle_.getParam("steering_servo/servo_ms/min_ms", min_ms_)) return false;
	if (!nodeHandle_.getParam("steering_servo/servo_ms/min_ms", max_ms_)) return false;

	return true;
}


void SteeringServo::topicCallback_(const geometry_msgs::Twist& msg)
{
	float percent = msg.angular.z;
	int ms;

	ms = min_ms_ + (max_ms_ - min_ms_)*(percent + 1.0)/2.0;

	servo_.writeMs(ms);
}

} /* namespace steering_servo */


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
	if (!nodeHandle_.getParam("steering_servo/servo_ms/max_ms", max_ms_)) return false;
	if (!nodeHandle_.getParam("steering_servo/servo_ms/neutral_ms", neutral_ms_)) return false;
	if (!nodeHandle_.getParam("steering_servo/servo_ms/use_way", use_way_)) return false;

	return true;
}


void SteeringServo::topicCallback_(const geometry_msgs::Twist& msg)
{
	int percent = msg.angular.z * 100;
	int ms;
	unsigned int max_ticks;

	if(percent >= 0)
	{
		max_ticks = max_ms_ - neutral_ms_;
		max_ticks = (max_ticks*use_way_)/100;
		ms = (percent * max_ticks)/100 + neutral_ms_;
	}

	if(percent < 0)
	{
		max_ticks = neutral_ms_ - min_ms_;
		max_ticks = (max_ticks*use_way_)/100;
		ms = (percent * max_ticks)/100 + neutral_ms_;
	}

	ROS_DEBUG_STREAM("ms written to servo: " << ms);

	servo_.writeMs(ms);
}

} /* namespace steering_servo */


#ifndef STEERING_SERVO_HPP
#define STEERING_SERVO_HPP

#include "servo.h"

// Ros
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

// Std
#include <string>

namespace steering_servo
{

class SteeringServo
{
public:
	SteeringServo(ros::NodeHandle& nodeHandle);

private:
	ros::NodeHandle& nodeHandle_;
	ros::Subscriber subscriber_;
	std::string subscriberTopic_;

	Servo servo_;

	// Functions
	bool readParameters_();
	void topicCallback_(const geometry_msgs::Twist& msg); //argument: const ... received message
};

} /* namespace steering_servo */

#endif // STEERING_SERVO_HPP

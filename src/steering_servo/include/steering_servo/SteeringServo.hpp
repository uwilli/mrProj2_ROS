#ifndef STEERING_SERVO_HPP
#define STEERING_SERVO_HPP

//#include "steering_servo/servo.h"

// Ros
#include <ros/ros.h>

// Std
#include <string>

namespace steering_servo
{

class SteeringServo
{
public:
	SteeringServo(const ros::NodeHandle& nodeHandle);

private:
	ros::NodeHandle& nodeHandle_;
	ros::Subscriber subscriber_;
	std::string subscriberTopic_;

	// Functions
	bool readParameters_();
	void topicCallback_(); //argument: const ... received message
};

} /* namespace steering_servo */

#endif // STEERING_SERVO_HPP

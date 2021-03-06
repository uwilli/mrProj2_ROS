#ifndef STEERING_SERVO_HPP
#define STEERING_SERVO_HPP

#include "servo.h"

// Ros
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

// Std
#include <string>


namespace mrcar_hardware_ctrl
{

class SteeringServo
{
public:
	SteeringServo(ros::NodeHandle& nodeHandle);

private:
	ros::NodeHandle& nodeHandle_;
	ros::Subscriber subscriber_;
	std::string subscriberTopic_;
	int min_ms_;
	int max_ms_;
	int neutral_ms_;
	int use_way_; // restrict servo to maximum movement, [0,100]

	Servo servo_;

	// Functions
	bool readParameters_();
	void topicCallback_(const geometry_msgs::Twist& msg); //argument: const ... received message
};

} /* namespace mrcar_hardware_ctrl */

#endif // STEERING_SERVO_HPP

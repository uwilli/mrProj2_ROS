#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "tb6612fng.h"

// Ros
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

// Std
#include <string>


namespace motor
{

class Motor
{
public:
	Motor(ros::NodeHandle& nodeHandle);

private:
	ros::NodeHandle& nodeHandle_;
	ros::Subscriber subscriber_;
	std::string subscriberTopic_;

	Tb6612fng m3_;

	// Functions
	bool readParameters_();
	void topicCallback_(const geometry_msgs::Twist& msg); //argument: const ... received message
};

} /* namespace motor */

#endif // MOTOR_HPP

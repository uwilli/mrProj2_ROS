#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "tb6612fng.h"

// Ros
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Time.h>

// Std
#include <string>


namespace mrcar_hardware_ctrl
{

class Motor
{
public:
	Motor(ros::NodeHandle& nodeHandle);

private:
	ros::NodeHandle& nodeHandle_;
	ros::Subscriber subscriber_;
	std::string subscriberTopic_;

	ros::Subscriber clock_subscriber_;
	std::string clock_subscriberTopic_;
	int clock_Hz_;
	int max_time_no_msg_;

	Tb6612fng m3_;

	std_msgs::Time time_last_msg_;

	// Functions
	bool readParameters_();
	void topicCallback_(const geometry_msgs::Twist& msg); //argument: const ... received message
	void clock_topicCallback_(const std_msgs::Time& msg);
	void check_namespace_topic_(const std::string& subTopic);
};

} /* namespace mrcar_hardware_ctrl */

#endif // MOTOR_HPP

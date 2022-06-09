#ifndef MOTOR_HPP
#define MOTOR_HPP


// Ros
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

// Std
#include <string>


namespace mrcar_hardware_ctrl
{

class Clock
{
public:
	Clock(ros::NodeHandle& nodeHandle);

private:
	ros::NodeHandle& nodeHandle_;
	ros::Subscriber subscriber_;
	std::string subscriberTopic_;


	// Functions
	bool readParameters_();
	void topicCallback_(const geometry_msgs::Twist& msg); //argument: const ... received message
};

} /* namespace mrcar_hardware_ctrl */

#endif // MOTOR_HPP

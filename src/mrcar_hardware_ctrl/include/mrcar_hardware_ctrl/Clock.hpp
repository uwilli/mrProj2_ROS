#ifndef MOTOR_HPP
#define MOTOR_HPP


// Ros
#include <ros/ros.h>
#include <std_msgs/Time.h>

// Std
#include <string>

namespace mrcar_hardware_ctrl
{


class Clock
{
public:
	Clock(ros::NodeHandle& nodeHandle);
	void publishTime();
	float getPeriod();
	int getHz();

private:
	ros::NodeHandle& nodeHandle_;
	ros::Publisher publisher_;
	std::string publisherTopic_;
	int publisher_Hz_;

	bool readParameters_();
};

} /* namespace mrcar_hardware_ctrl */

#endif // MOTOR_HPP

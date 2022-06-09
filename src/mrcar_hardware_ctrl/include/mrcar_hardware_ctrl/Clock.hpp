#ifndef MOTOR_HPP
#define MOTOR_HPP


// Ros
#include <ros/ros.h>
#include <std_msgs/String.h>

// Std
#include <string>

namespace mrcar_hardware_ctrl
{


class Clock
{
public:
	Clock(ros::NodeHandle& nodeHandle);
	void publishTime();

private:
	ros::NodeHandle& nodeHandle_;
	ros::Publisher publisher_;
	std::string publisherTopic_;

	bool readParameters_();
};

} /* namespace mrcar_hardware_ctrl */

#endif // MOTOR_HPP

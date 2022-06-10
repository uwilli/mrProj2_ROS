#ifndef XBOX_CONTROLLER_HPP
#define XBOX_CONTROLLER_HPP


// Ros
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

// Std
#include <string>

namespace mrcar_hardware_ctrl
{


class XboxController
{
public:
	XboxController(ros::NodeHandle& nodeHandle);
	void publish();
	float getPeriod();

private:
	ros::NodeHandle& nodeHandle_;
	ros::Publisher publisher_;
	std::string publisherTopic_;
	int publisher_Hz_;

	bool readParameters_();
};

} /* namespace mrcar_hardware_ctrl */

#endif // MOTOR_HPP

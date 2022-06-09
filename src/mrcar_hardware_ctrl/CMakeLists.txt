#################################################################################
# Use this reduced CMakeLists.txt to build on local develop machine
# Add src files below in add executable
#################################################################################

cmake_minimum_required(VERSION 3.0.2)
project(mrcar_hardware_ctrl)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
)

catkin_package(
	INCLUDE_DIRS
		include

	CATKIN_DEPENDS
		roscpp
		geometry_msgs
)

include_directories(
	include
  		${catkin_INCLUDE_DIRS}
  		~/mrProj2/source/inc
)

add_executable(${PROJECT_NAME}
	src/steering_servo_node.cpp
	src/SteeringServo.cpp
	src/motor_node.cpp
	src/Motor.cpp
)

target_link_libraries(${PROJECT_NAME}
   ${catkin_LIBRARIES}
)



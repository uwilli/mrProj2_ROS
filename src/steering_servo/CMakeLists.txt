cmake_minimum_required(VERSION 3.0.2)
project(steering_servo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
	INCLUDE_DIRS
		include
#  LIBRARIES steering_servo
	CATKIN_DEPENDS
		roscpp
		geometry_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

# Pigpiod: Run classes raspiPigpio etc with define DAEMON for ability of running multiple programs simultaneously
add_compile_definitions(DAEMON)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
	include
  		${catkin_INCLUDE_DIRS}
  		~/mrProj2/source/inc
)

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(${PROJECT_NAME}
	src/steering_servo_node.cpp
	src/SteeringServo.cpp
	~/mrProj2/source/src/servo.cpp
	~/mrProj2/source/src/pigpioPwm.cpp
	~/mrProj2/source/src/raspiPigpio.cpp
)

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}
   ${catkin_LIBRARIES}
   pigpio
   ${pigpiod_if2_LIBRARY}
 )

#############
## Install ##
#############

## Mark executables for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_executables.html
install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
 )


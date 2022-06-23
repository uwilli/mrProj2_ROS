# mrProj2_ROS
Ros catkin ws for Mobile Robotics project 2 (FHGR).
Hardware used is a Raspberry Pi 4b (4Gb) and a custom PCB. Check out [mrProj2](https://github.com/uwilli/mrProj2) repository for ROS-independent C++ classes driving the GPIOs with pigpio.

Prerequisite: Ros installation (noetic used) on the raspberry pi.

This project includes ROS packages for steering and speed control on a small scale car. It can be commanded via an xbox controller or an 3D Connexion Spacemouse Pro Wireless. Also included are a copy of a package for the 2d Lidar and of the hector_slam package. Links to source below.
From the hector_slam, basic mapping is setup.

[Demo Video](https://youtu.be/WBXDojHb8BE)

## Open source ROS packages
[hector_slam](https://github.com/tu-darmstadt-ros-pkg/hector_slam)  
[rp_lidar_ros](https://github.com/Slamtec/rplidar_ros)


## Ros commands

#### Publish cmd_vel
	$ rostopic pub /mrcar_hardware_ctrl/cmd_vel geometry_msgs/Twist "{linear: {x: 0, y: 0, z: 0}, angular: {x: 0, y: 0, z: -1}}"


## ROS-Helpers

#### Added to ~/.bashrc

	# Start ssh-agent and add  key for git
	eval "$(ssh-agent -s)"
	ssh-add ~/.ssh/githubFHGR.txt 2>/dev/null
	
	# Alias definitions 
	alias ..="cd .."
	alias sr="source devel/setup.bash"
	alias ws="cd ~/catkin_ws"
	alias re="cd ~/catkin_ws && git pull && catkin build && source devel/setup.bash"
	alias la="cd ~/catkin_ws && roslaunch src/project.launch"
	
	# Functions
	bd() { catkin build "$1" && source devel/setup.bash; }
	source ~/catkin_ws/devel/setup.bash
	
##### bash functions
For function bd() added in .bashrc  
Create file /etc/bash_completion.d/bd_bashfunction-completion.bash
Content:  
	# Copyright 2015 Open Source Robotics Foundation, Inc.
	#
	# Licensed under the Apache License, Version 2.0 (the "License");
	# you may not use this file except in compliance with the License.
	# You may obtain a copy of the License at
	#
	#     http://www.apache.org/licenses/LICENSE-2.0
	#
	# Unless required by applicable law or agreed to in writing, software
	# distributed under the License is distributed on an "AS IS" BASIS,
	# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	# See the License for the specific language governing permissions and
	# limitations under the License.

	# ZSH support
	if [[ -n ${ZSH_VERSION-} ]]; then
	  autoload -U +X bashcompinit && bashcompinit
	fi
	_catkin_pkgs()
	{
	  # return list of all packages
	  catkin --no-color list --unformatted --quiet 2> /dev/null
	}

	_bd()
	{
	  local cur prev words cword catkin_verbs catkin_opts
	  _init_completion || return # this handles default completion (variables, redirection)

	  COMPREPLY=($(compgen -W "$(_catkin_pkgs)" -- ${cur}))
	      
	  return 0
	}

	complete -F _bd bd


	
#### Git config
	$ git config --global user.name "John Doe"
	$ git config --global user.email "johndoe@example.net"
	$ git config --global core.editor nano
	$ git config --global alias.st status
	$ git config --global alias.co checkout
	$ git config --global alias.ci commit
	
	
## Troubleshooting
#### Yaml files (param server)
Only spaces allowed, no tabs!


# mrProj2_ws
Ros catkin ws for Mobile Robotics project 2 (FHGR).






## ROS-Helpers

#### Added to ~/.bashrc

	# Start ssh-agent and add  key for git
	eval "$(ssh-agent -s)"
	ssh-add ~/.ssh/githubFHGR.txt
	
	# Alias definitions 
	alias ..="cd .."
	alias sr="source devel/setup.bash"
	alias ws="cd ~/catkin_ws"
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


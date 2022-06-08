cmake_minimum_required(VERSION 2.8.3)
project(python_package_template)

find_package(catkin REQUIRED)

catkin_package()

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
catkin_install_python(PROGRAMS
   python_package_template.py
   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)


cmake_minimum_required(VERSION 3.0.2)
project(follow_waypoint)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  actionlib
  geometry_msgs
  move_base
  roscpp
  std_msgs
)
catkin_package(
   LIBRARIES ${PROJECT_NAME}
   CATKIN_DEPENDS
   actionlib
  geometry_msgs
  move_base
  roscpp
  std_msgs
)
include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)
## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
#
add_executable(follow_waypoint src/follow_waypoint.cpp)
## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")
target_link_libraries(follow_waypoint ${catkin_LIBRARIES})
## Add cmake target dependencies of the executable
## same as for the library above
 add_dependencies(follow_waypoint ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
#

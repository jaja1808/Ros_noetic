#include <ros/ros.h>
#include "two_robot_control/aruco_follow.hpp"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "two_robot_control");
  ros::NodeHandle nodeHandle("~");

  two_robot_control::Aruco_follower follow (nodeHandle);
  
  ros::spin();
  return 0;
}
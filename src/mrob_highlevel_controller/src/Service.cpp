#include <ros/ros.h>
#include <mrob_highlevel_controller/SetBoolClient.hpp>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "mrob_obstactle_detector");
  ros::NodeHandle ClientHandle("~");

  mrob_highlevel_controller::SetBoolClient vel_command(ClientHandle);
  
  ros::spin();
  return 0;
}

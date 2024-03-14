#include <ros/ros.h>
#include <mrob_highlevel_controller/ImuClient.hpp>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "mrob_imu_detector");
  ros::NodeHandle Imu_ClientHandle("~");

  mrob_highlevel_controller::ImuClient imu_based_command(Imu_ClientHandle);
  
  ros::spin();
  return 0;
}

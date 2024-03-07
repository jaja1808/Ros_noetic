#include <ros/ros.h>
#include "two_robot_control/leader.hpp"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "two_robot_control");
    ros:NodeHandle modeHamdle("~");

    two_robot_control::leader(NodeHandle);
    

    ros::spin();
    return 0;
}
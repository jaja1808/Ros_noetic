#pragma once

// ROS
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <std_srvs/SetBool.h>

namespace mrob_highlevel_controller {
/*!
 * Main class for the node to handle the ROS interfacing.
 */
class SetBoolClient
{

private:
    //! ROS nodeHandle
    ros::NodeHandle ClientHandle_;
    //! ROS Client
    ros::ServiceClient Observer_;
    //! ROS Scan subscriber
    ros::Subscriber scanner_;
    
    // Callback function
    void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg);

public:
  /*!
   * Constructor.
   * @param clientHandle the ROS node handle.
   */
  SetBoolClient(ros::NodeHandle& ClientHandle);

};

}
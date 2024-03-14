#pragma once

// ROS
#include <ros/ros.h>
#include <std_srvs/SetBool.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>

namespace mrob_highlevel_controller {
/*!
 * Main class for the node to handle the ROS interfacing.
 */
class HighlevelController
{
 public:
  /*!
   * Constructor.
   * @param nodeHandle the ROS node handle.
   */
  HighlevelController(ros::NodeHandle& nodeHandle);

  /*!
   * Destructor.
   */
  virtual ~HighlevelController();

 private:
  //! ROS node handle.
  ros::NodeHandle& nodeHandle_;
  //! ROS Scan subscriber
  ros::Subscriber scanSubscriber_;
  //! ROS Twist publisher
  ros::Publisher twistPublisher_;
  //! ROS Marker publisher
  ros::Publisher visual_marker_;
  //! ROS SetBool Server
  ros::ServiceServer start_stop_;
  
  // Movement 
  bool forward = true;
  
  // Callback function
  void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg);

  // Callback function of the service
  bool stop_or_start(std_srvs::SetBool::Request& request,
            std_srvs::SetBool::Response& responnse);
};

} /* namespace */

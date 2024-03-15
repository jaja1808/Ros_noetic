#pragma once

// ROS
#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Vector3Stamped.h>

namespace two_robot_control {

class Aruco_follower{

     private:
    //! ROS node handle.
    ros::NodeHandle& nodeHandle_;
    //! ROS Scan subscriber
    ros::Subscriber Aruco_Subscriber_;
    //! ROS Twist publisher
    ros::Publisher Velocity_Publisher_;

    public:
        /*!
        * Constructor.
        * @param nodeHandle the ROS node handle.
        */
        Aruco_follower(ros::NodeHandle& nodeHandle);  
    
    // Callback function
    void arucoCallback(const geometry_msgs::Vector3Stamped::ConstPtr& pose);
};
} /* namespace */

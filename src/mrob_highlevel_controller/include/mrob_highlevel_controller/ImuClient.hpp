#pragma once

#include  <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <std_srvs/SetBool.h>

namespace mrob_highlevel_controller{

    class ImuClient{

    private:
        // Create the node object
        ros::NodeHandle&  Imu_ClientHandle_;
        // Create the sensor subscriber
        ros::Subscriber imu_subscriber_;
        // Create the client to SetBool Service
        ros::ServiceClient imu_observer_;

        // Imu Callback function
        void imuCallback(const sensor_msgs::Imu::ConstPtr& message);

    public:
        /*!
   * Constructor.
   * @param imuClientHandle the ROS node handle.
   */
    ImuClient(ros::NodeHandle& imuClientHandle);

    };
    
}

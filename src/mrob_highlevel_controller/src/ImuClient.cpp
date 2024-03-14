#include "mrob_highlevel_controller/ImuClient.hpp"
#include "sensor_msgs/Imu.h"
#include "std_srvs/SetBool.h" 

#include <string.h>
#include <cmath>

namespace mrob_highlevel_controller {

    void ImuClient::imuCallback(const sensor_msgs::Imu::ConstPtr& message){
        // acceleration
        float x_linear_acceleration = message->linear_acceleration.x;
        float y_linear_acceleration = message->linear_acceleration.y;
        ROS_INFO_STREAM("the linear acceleration on x is " << x_linear_acceleration << "and linear acceleration on y " << y_linear_acceleration);

        // Create a service request object
        std_srvs::SetBool srv;
        float deceleration;

        Imu_ClientHandle_.getParam("deceleration", deceleration);
        
        // If the robot is too close to an obstacle
        if (x_linear_acceleration < deceleration && y_linear_acceleration < deceleration){
            srv.request.data = false;
        }else{
            srv.request.data = true;
        }

        // Call the service using the service client object
        if (imu_observer_.call(srv)){
            ROS_INFO("IMU Successfully sent the bool value to the server");
        }else{
            ROS_ERROR("IMU Failed to call service");
        }
    }

ImuClient::ImuClient(ros::NodeHandle &imuClientHandle): Imu_ClientHandle_(imuClientHandle){
    // Declare Scan parameters
    std::string imu_topic;
    int queue_size;
    // Server parameter
    std::string service_name;
    // Client name
    std::string imu_client_name;

    // Getting the paraameters from a param file
    Imu_ClientHandle_.getParam("imu_topic", imu_topic);
    Imu_ClientHandle_.getParam("queue_size", queue_size);
    Imu_ClientHandle_.getParam("client_name", imu_client_name);
    Imu_ClientHandle_.getParam("service_name", service_name);

    // If the parameters are found
    ROS_INFO_STREAM("The IMU SUBSCRIBER is: " << imu_topic << " and " << queue_size << " The IMU client name is: " << imu_client_name <<" The Service name is "<<service_name);
    
    // Subscription
    imu_subscriber_ = Imu_ClientHandle_.subscribe(imu_topic, queue_size, &ImuClient::imuCallback, this);
    //Imu client
    imu_observer_ = Imu_ClientHandle_.serviceClient<std_srvs::SetBool>(service_name);
}
}

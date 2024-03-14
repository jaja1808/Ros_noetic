#include "mrob_highlevel_controller/SetBoolClient.hpp"
#include "sensor_msgs/LaserScan.h"
#include "std_srvs/SetBool.h"
#include <string.h>
#include<cmath>

namespace mrob_highlevel_controller {

// Callback function for the laser scan topic
void SetBoolClient::scanCallback(const sensor_msgs::LaserScan::ConstPtr &msg){
    // Distance
    float  min_distance = msg->ranges[0];

    // Loop through the ranges in the laser scan message
    for(int i = 0; i < msg->ranges.size(); i ++){
        // if the value in range is smaller or bigger than min_value
        if(msg->ranges[i] < min_distance){
            min_distance = msg->ranges[i];
        }
    }
    //Prinnce the min distances from client
    ROS_INFO_STREAM("The client reads distancee is " << min_distance);

    // Create a service request object
    std_srvs::SetBool srv;

    // If the robot is too close to an obstacle
    if (min_distance == msg->range_min){
        srv.request.data = false;
    }else{
        srv.request.data = true;
    }

    // Call the service using the service client object
    if (Observer_.call(srv)){
        ROS_INFO("Successfully sent the bool value to the server");
    }else{
        ROS_ERROR("Failed to call service");
    }
}

SetBoolClient::SetBoolClient(ros::NodeHandle &ClientHandle): ClientHandle_(ClientHandle){
    // Declare Scan parameters
    std::string subscriber_topic;
    int queue_size;
    // Server parameter
    std::string service_name;
    // Client name
    std::string client_name;

    // Getting the paraameters from a param file
    ClientHandle_.getParam("subscriber_topic", subscriber_topic);
    ClientHandle_.getParam("queue_size", queue_size);
    ClientHandle_.getParam("client_name", client_name);
    ClientHandle_.getParam("service_name", service_name);

    // Checking if the Parameters are found
    if(!(ClientHandle_.getParam("subscriber_topic", subscriber_topic) && ClientHandle_.getParam("queue_size", queue_size) &&
           ClientHandle_.getParam("client_name", client_name) && ClientHandle_.getParam("service_name", service_name))){

            ROS_INFO(" Parameters not found !");
           }
    // If the parameters are found
    ROS_INFO_STREAM("The parameter is: " << subscriber_topic << " and " << queue_size << " The client name is: " <<client_name<<" The Service name is "<<service_name);
    
    // Defining my subscriber node
    scanner_ = ClientHandle_.subscribe(subscriber_topic, queue_size, &SetBoolClient::scanCallback, this);
    Observer_ = ClientHandle_.serviceClient <std_srvs::SetBool> (service_name);
}
}
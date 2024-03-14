#include "mrob_highlevel_controller/HighlevelController.hpp"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "visualization_msgs/Marker.h"
#include "std_srvs/SetBool.h"
#include <cmath>

// STD
#include <string>

namespace mrob_highlevel_controller {

HighlevelController::HighlevelController(ros::NodeHandle& nodeHandle)
    : nodeHandle_(nodeHandle)
{   
    // Declare Scan parameters
    std::string subscriber_topic;
    int queue_size;
    // Declare Twist parameters
    std::string twist_topic;
    int twist_queue;
    // Visualization parameters
    std::string marker_topic;
    int marker_queue;
    // Server parameter
    std::string service_name;

    // Get the parameters
    nodeHandle_.getParam("subscriber_topic", subscriber_topic);
    nodeHandle_.getParam("queue_size", queue_size);
    nodeHandle_.getParam("twist_topic", twist_topic);
    nodeHandle_.getParam("twist_queue", twist_queue);
    nodeHandle_.getParam("marker_topic", marker_topic);
    nodeHandle_.getParam("marker_queue", marker_queue);
    nodeHandle_.getParam("service_name", service_name);


    // Checking if the Parameters are found
    if(!(nodeHandle_.getParam("subscriber_topic", subscriber_topic) && nodeHandle_.getParam("queue_size", queue_size) &&
           nodeHandle_.getParam("twist_topic", twist_topic) && nodeHandle_.getParam("twist_queue", twist_queue) &&
           nodeHandle_.getParam("marker_topic", marker_topic) && nodeHandle_.getParam("marker_queue", marker_queue))){

            ROS_INFO(" Parameters not found !");
           }

    // If the parameters are found
    ROS_INFO_STREAM("The parameter is: " << subscriber_topic << " and " << queue_size);
    // Defining my subscriber node
    scanSubscriber_ = nodeHandle_.subscribe(subscriber_topic, queue_size, &HighlevelController::scanCallback, this);
    
    // If the parameters are found
    ROS_INFO_STREAM("The parameters are: " << twist_topic << " and " << twist_queue);
    // Defining my publisher node
    twistPublisher_ = nodeHandle_.advertise <geometry_msgs::Twist> (twist_topic, twist_queue);

    // Defining the visualization marker
    visual_marker_ = nodeHandle_.advertise <visualization_msgs::Marker> (marker_topic, marker_queue);

    // Defining the Server for starting and stopping 
    start_stop_ = nodeHandle_.advertiseService (service_name, &HighlevelController::stop_or_start, this);
}

HighlevelController::~HighlevelController()
{
}

// Callback function to handle the incoming laser scan
void HighlevelController::scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg){
    
    //  Defining the minimum as the first value 
    float  min_value = msg->ranges[0];
    float  angle = msg->angle_increment;
    float  max_value = msg->ranges[0];
    int  index = 0;
    float linear_speed;
    float angular_speed;
    
    // Going through the ranges 
    for(int i = 0; i < msg->ranges.size(); i ++){
        
        // if the value in range is smaller or bigger than min_value
        if(msg->ranges[i] < min_value){
            min_value = msg->ranges[i];
            index = i;
        }

        if (msg->ranges[i]> max_value && msg->ranges[i]<msg->range_max){
            max_value = msg->ranges[i];
        }
    } 
        // calculationg the angle 
        angle = (msg->angle_min + index * angle);

        // Pillar coordinates
        float pil_x = min_value * cos(angle);
        float pil_y = min_value * sin(angle);

        // Angle Position of the pillar
        angle = atan2f(pil_y,pil_x);
        ROS_INFO("Angle with atan is: %f", angle);

        // Print the INFO
        ROS_INFO_STREAM("The minimum distance is : " << min_value << " at index : " << index << " and the maximum distance is : " << max_value);
        ROS_INFO("Pillar x-coordinate is: %f and y-coordinate is %f", pil_x, pil_y);

        // Publishing a Twist command
        geometry_msgs::Twist movement;

        // Get Parameters of speed
        nodeHandle_.getParam("angular_speed", angular_speed);
        nodeHandle_.getParam("linear_speed", linear_speed);
        
        // Print the Velocities
        ROS_INFO_STREAM("The angular and linear velocities are: " << angular_speed << " and " << linear_speed);

        // PARSING THE VELOCITIES
        if (forward){
            movement.linear.x = linear_speed;
            movement.angular.z = angular_speed * angle;
        }else{
            movement.linear.x = 0;
            movement.angular.z = 0;
        }
        // Movement of the robot
        twistPublisher_.publish(movement);

        // RVIZ Marker
        visualization_msgs::Marker marker;
        marker.header.frame_id = "base_scan";
        marker.header.stamp = ros::Time::now();
        marker.ns = "mrob_highlevel_controller";
        marker.id = 0;
        marker.type = visualization_msgs::Marker::SPHERE;
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose.position.x = pil_x;
        marker.pose.position.y = pil_y;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;
        marker.scale.x = 0.1;
        marker.scale.y = 0.1;
        marker.scale.z = 0.1;
        marker.color.a = 1.0; // Don't forget to set the alpha!
        marker.color.r = 0.9;
        marker.color.g = 1.0;
        marker.color.b = 0.0;

        visual_marker_.publish(marker);
}

bool HighlevelController::stop_or_start(std_srvs::SetBool::Request &request,
    std_srvs::SetBool::Response &response){ 

        if (request.data && forward){

            forward = true;
            ROS_INFO("There is movement");
            response.success = true;
            response.message = "Robot is moving";

        }else{
            forward = false;
            ROS_INFO("Stop");
            response.success = true;
            response.message = "Robot is stopping";
        }
    return true;
}
} /* namespace */

#include "two_robot_control/aruco_follow.hpp"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Vector3Stamped.h"
#include "geometry_msgs/Twist.h"
#include <cmath>

//STD
#include <string>

namespace two_robot_control{

   Aruco_follower::Aruco_follower(ros::NodeHandle& nodeHandle): nodeHandle_(nodeHandle){

    // Declare Aruco Subscriber parameters
    std::string aruco_topic;
    int aruco_queue ;
    // Declare Follower Velocity Publisher
    std::string cmd_vel_topic;
    int cmd_vel_queue;

    // Get the parameters
    nodeHandle_.getParam("aruco_topic", aruco_topic);
    nodeHandle_.getParam("aruco_queue", aruco_queue);
    nodeHandle_.getParam("cmd_vel_topic", cmd_vel_topic);
    nodeHandle_.getParam("cmd_vel_queue", cmd_vel_queue);

    // Checking if the Parameters are found
    if(!(nodeHandle_.getParam("aruco_topic", aruco_topic) && nodeHandle_.getParam("aruco_queue", aruco_queue) && 
        nodeHandle_.getParam("cmd_vel_topic", cmd_vel_topic) && nodeHandle_.getParam("cmd_vel_queue", cmd_vel_queue))){

        ROS_INFO(" Parameters not found !");
        }
    
    // If the parameters are found
    ROS_INFO_STREAM("The Aruco parameter is: " << aruco_topic << " at queue of: " << aruco_queue);
    // Defining my subscriber node
    Aruco_Subscriber_ = nodeHandle_.subscribe(aruco_topic, aruco_queue, &Aruco_follower::arucoCallback, this);
    // Defining my publisher node
    Velocity_Publisher_ = nodeHandle_.advertise <geometry_msgs::Twist> (cmd_vel_topic, cmd_vel_queue);
}

void Aruco_follower::arucoCallback(const geometry_msgs::Vector3Stamped::ConstPtr &pose){

    // Declare the Variables
    float x = pose->vector.x;
    float y = pose->vector.y;
    float z = pose->vector.z;
    
    //Speed 
    float linear_vel;
    float angular_vel;
    
    // getting parameters
    nodeHandle_.getParam("linear_vel", linear_vel);
    nodeHandle_.getParam("angular_vel", angular_vel);

    ROS_INFO_STREAM("Values of x: " << x << "y: "<< y << "z: " << z);

    // Angle Position of the leader
    float angle = atan2f(z, x);
    ROS_INFO("Angle with atan is: %f", angle);

    // movement to be published
    geometry_msgs::Twist move;

    // Move robot
    move.linear.x = linear_vel;
    move.angular.y = angular_vel * angle;

    //Publisher to Publish the velocities
    Velocity_Publisher_.publish(move);
}
}
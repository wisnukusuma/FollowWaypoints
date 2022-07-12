#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PointStamped.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Point.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
// Define a client for to send goal requests to the move base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
std::vector<std::vector<float> > pose;

void read_record()
{

	// File pointer

	std::ifstream fin;
	// Open an existing file
	fin.open("/home/wisnu/catkin_ws/waypoints/waypoint.csv");
	
	std::string line, word, temp;
	if (fin.is_open()){
	while (std::getline(fin, line)) {

		std::vector<float> col;
		// read an entire row and
		// store it in a string variable 'line'
		
		std::cout<<line;
		// used for breaking words
		std::stringstream s(line);

		// read every column data of a row and
		// store it in a string variable, 'word'
		while (std::getline(s, word, ',')) {

			// add all the column data
			// of a row to a vector
			
			col.push_back(std::stof(word));
		}
		pose.push_back(col);
		// convert string to integer for comparision
		// Compare the roll number
	}
	fin.close();
	for (int i = 0; i < pose.size(); i++) {
        for (int j = 0; j < pose[i].size(); j++)
            ROS_INFO("%f,",pose[i][j]);     

       }
       }
       
}

int main(int argc, char** argv){
	// Initialize the simple navigation goals node  
	ros::init(argc,argv,"follow_waypoint");
	read_record();
	MoveBaseClient ac("move_base", true);
	// Wait 5 sec for move base action server to come up
	while(!ac.waitForServer (ros::Duration(1.0))){
		ROS_INFO("mbut for the move_base action server to come up");
	}
	move_base_msgs::MoveBaseGoal goal;
	// set up the frame parameters
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();

	
	for (int i =0; i< pose.size(); i++){
		// Define a position and orientation for the robot to reach
		goal.target_pose.pose.position.x = pose[i][0];
		goal.target_pose.pose.position.y = pose[i][1];
		goal.target_pose.pose.orientation.w = 1;
		// Send the goal position and orientation for the robot to reach
		ROS_INFO("Sending goal");
		ac.sendGoal (goal);
		// Wait an infinite time for the results
		ac.waitForResult();
		ROS_INFO("reach the [%f],[%f]",pose[i][0],pose[i][1]);
	} 
	// Check if the robot reached ts goal
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		ROS_INFO( "Hooray, reached drop off zone");
	else
		ROS_INFO("The base failed to move forward");
	return 0;
}

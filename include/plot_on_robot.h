


#include "eigen3/Eigen/Dense"

#include "MathLib.h"



#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "ros/ros.h"
#include <iostream>
#include <math.h>
#include "kuka_fri_bridge/JointStateImpedance.h"
#include "sensor_msgs/JointState.h"

#include "mathlib_eigen_conversions.h"

const char *Positioncolided_path="/home/sina/Dropbox/Sinas_stuff/catkin_ws/underlay/src/Data_Analysis/constructing_data_set/data/Collision_Complete.txt";
const char *PositionNeighbour_path="/home/sina/Dropbox/Sinas_stuff/catkin_ws/underlay/src/Data_Analysis/constructing_data_set/data/Neighbour_Complete.txt";
ros::Publisher pub_command_pos_left;
ros::Publisher pub_command_pos_right;
ros::Subscriber 			sub_left_position;
ros::Subscriber 			sub_right_position;

int KUKA_DOF=7;
MathLib::Vector Position;
MathLib::Vector JointPos;


void Send_Postion_To_Robot(MathLib::Vector Position)
{
	kuka_fri_bridge::JointStateImpedance msg;

	msg.position.resize(KUKA_DOF);
	msg.stiffness.resize(KUKA_DOF);
	for (int i=0; i<KUKA_DOF;i=i+1)
	{
		msg.stiffness[i] = 2000;
	}


	MathLib::Vector Position_Right(7);
	MathLib::Vector Position_left(7);

	msg.position[0]=Position(0);		msg.position[1]=Position(1);		msg.position[2]=Position(2);
	msg.position[3]=Position(3);		msg.position[4]=Position(4);		msg.position[5]=Position(5);
	msg.position[6]=Position(6);



	pub_command_pos_left.publish(msg);


	msg.position[0]=Position(7);		msg.position[1]=Position(8);		msg.position[2]=Position(9);
	msg.position[3]=Position(10);		msg.position[4]=Position(11);		msg.position[5]=Position(12);
	msg.position[6]=Position(13);


	pub_command_pos_right.publish(msg);



}

void chatterCallback_left_position(const sensor_msgs::JointState & msg)
{
	JointPos(0)=msg.position[0];
	JointPos(1)=msg.position[1];
	JointPos(2)=msg.position[2];
	JointPos(3)=msg.position[3];
	JointPos(4)=msg.position[4];
	JointPos(5)=msg.position[5];
	JointPos(6)=msg.position[6];


}

void chatterCallback_right_position(const sensor_msgs::JointState & msg)
{
	JointPos(7)=msg.position[0];
	JointPos(8)=msg.position[1];
	JointPos(9)=msg.position[2];
	JointPos(10)=msg.position[3];
	JointPos(11)=msg.position[4];
	JointPos(12)=msg.position[5];
	JointPos(13)=msg.position[6];
}

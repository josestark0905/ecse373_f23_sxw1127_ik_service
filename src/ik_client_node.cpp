#include "ros/ros.h"
#include <cstdlib>
#include "ik_service/PoseIK.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ik_client_node");
  
  ik_service::PoseIK ik_pose;
  geometry_msgs::Pose part_pose;
  
  part_pose.position.x = 0.5;
  part_pose.position.y = 0;
  part_pose.position.z = 0;
  ROS_WARN("Ask the server x = %f, y = %f, z = %f", part_pose.position.x, part_pose.position.y, part_pose.position.z);
  
  ik_pose.request.part_pose = part_pose;

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<ik_service::PoseIK>("pose_ik");
    
  if (client.call(ik_pose))
  {
    ROS_INFO("Call to ik_service returned [%i] solutions", ik_pose.response.num_sols);
    for(int i=0; i<ik_pose.response.num_sols; i++){
    	ROS_INFO("------------------------------------------");
    	ROS_INFO("Solution %d:", i+1);
    	for(int j=0; j<6; j++){
    		ROS_INFO("%f", ik_pose.response.joint_solutions[i].joint_angles[j]);
    	}
    }
  }
  else
  {
    ROS_ERROR("Failed to call service ik");
    return 1;
  }

  return 0;
}

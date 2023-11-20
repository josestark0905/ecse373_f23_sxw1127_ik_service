#include "ros/ros.h"
#include <cstdlib>
#include "ik_service/PoseIK.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ik_client");
  
  ik_service::PoseIK ik_pose;
  geometry_msgs::Pose part_pose;
  
  part_pose.position.x = 0.5;
  part_pose.position.y = 0;
  part_pose.position.z = 0;
  
  ik_pose.request.part_pose = part_pose;

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<ik_service::PoseIK>("pose_ik");
    
  if (client.call(ik_pose))
  {
    ROS_INFO("Call to ik_service returned [%i] solutions", ik_pose.response.num_sols);
    
  }
  else
  {
    ROS_ERROR("Failed to call service ik");
    return 1;
  }

  return 0;
}

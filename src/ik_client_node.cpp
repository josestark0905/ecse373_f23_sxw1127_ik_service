#include "ros/ros.h"
#include <cstdlib>
#include "ik_service/PoseIK.h"
#include "ur_kinematics/ur_kin.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ik_client");
  
  ik_service::PoseIK ik_pose;
  geometry_msgs::Pose part_pose;
  
  part_pose.position.x = 0.5;
  ik_pose.request.part_pose =  part_pose;

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<ik_service::PoseIK>("pose_ik");
  
  double q[] = {3.14, -1.13, 1.51, 3.77, -1.51, 0};
  double T[4][4];
  ur_kinematics::forward((double *)&q[0], (double *)&T[0][0]);
  
  int num_sol;
  double q_sols[8][6];
  num_sol = ur_kinematics::inverse(&T[0][0], &q_sols[0][0], 0.0);
  
  ROS_INFO("GET %i solutions", num_sol);
    
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

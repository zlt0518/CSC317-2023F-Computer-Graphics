#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function

Eigen::Affine3d forward_kinematics_helper(const Skeleton & skeleton, int index);

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  T.resize(skeleton.size(),Eigen::Affine3d::Identity());
  for(int i = 0;i<skeleton.size();i++)
  {
    T[i] = forward_kinematics_helper(skeleton,i);
  } 

}


Eigen::Affine3d forward_kinematics_helper(const Skeleton & skeleton, int index)
{
  if(index == -1)
  {
    //base case for no associated weights
    return Eigen::Affine3d::Identity();
  }

  int p_index = skeleton[index].parent_index;
  
  Eigen::Affine3d parent_transform = forward_kinematics_helper(skeleton, p_index);

  Eigen::Vector3d current_angle = skeleton[index].xzx;
  Eigen::Affine3d rotation = euler_angles_to_transform(current_angle);
  Eigen::Affine3d rest_space = skeleton[index].rest_T;

  return parent_transform* rest_space* rotation * (rest_space.inverse());


}


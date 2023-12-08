#include "transformed_tips.h"
#include "forward_kinematics.h"

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  Eigen::VectorXd return_tips = Eigen::VectorXd::Zero(3*b.size());

  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > T;
  forward_kinematics(skeleton, T);

  for (int i = 0; i < b.rows() ; i++) {
    
    Bone bone_curr = skeleton[b[i]]; 

    Eigen::Vector4d tip_curr = T[b[i]] * (bone_curr.rest_T * Eigen::Vector4d(bone_curr.length, 0, 0, 1));

    return_tips[3 * i] = tip_curr[0];
    return_tips[3 * i + 1] = tip_curr[1];
    return_tips[3 * i + 2] = tip_curr[2];
  }  

  return return_tips;

}

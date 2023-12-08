#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
  J = Eigen::MatrixXd::Zero(b.size()*3,skeleton.size()*3);
  auto tip_main = transformed_tips(skeleton, b);  
  
  double epsilon = 1e-7;

  for (int i = 0; i < skeleton.size(); i ++)
  {
    for(int j = 0;j < 3; j++)
    {
      auto skeleton_copy = skeleton;
      skeleton_copy[i].xzx[j] += epsilon;
      auto tip_curr = transformed_tips(skeleton_copy, b);
      
      J(0, 3 * i + j) = (tip_curr-tip_main)[0] / epsilon;
      J(1, 3 * i + j) = (tip_curr-tip_main)[1] / epsilon;
      J(2, 3 * i + j) = (tip_curr-tip_main)[2] / epsilon;
    }
  }  

}

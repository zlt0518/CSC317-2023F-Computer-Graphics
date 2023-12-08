#include "linear_blend_skinning.h"

void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{
  U.resize(V.rows(),3);

  for(int i = 0;i<V.rows();i++)
  {
    Eigen::Vector4d weighted_sum = Eigen::Vector4d::Zero();

    for (int j = 0; j < skeleton.size(); j++)
    {
      auto position_curr = Eigen::Vector4d(V(i,0),V(i,1),V(i,2),1);
      //loop through bones
      if (skeleton[j].weight_index == -1)
      {
        continue;
      }
      else
      {
        auto wight_curr = W(i,skeleton[j].weight_index); 
        auto trans_curr = T[j];
        
        weighted_sum += wight_curr* ( trans_curr * position_curr );
      }
    }

    for(int j = 0;j<U.cols();j++)
    {
      U(i,j) = weighted_sum[j];
      U(i,j) = weighted_sum[j];
      U(i,j) = weighted_sum[j];
    }
  }

}
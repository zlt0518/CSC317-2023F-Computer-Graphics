#include "copy_skeleton_at.h"
Skeleton copy_skeleton_at(
  const Skeleton & skeleton, 
  const Eigen::VectorXd & A)
{
  auto copy_skeleton = skeleton;

  for (int i = 0; i < skeleton.size(); i++) {
    copy_skeleton[i].xzx[0] = A[3*i];
    copy_skeleton[i].xzx[1] = A[3*i+1];
    copy_skeleton[i].xzx[2] = A[3*i+2];
  }

  return copy_skeleton;
}

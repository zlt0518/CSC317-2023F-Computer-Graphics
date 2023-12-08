#include "euler_angles_to_transform.h"

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
  // Reference: http://eecs.qmul.ac.uk/~gslabaugh/publications/euler.pdf
  Eigen::Affine3d x, y, z;

  x.matrix() << 
    1, 0, 0, 0,
    0, cos(xzx[0] * M_PI / 180.0), -sin(xzx[0] * M_PI / 180.0), 0,
    0, sin(xzx[0] * M_PI / 180.0), cos(xzx[0] * M_PI / 180.0), 0,
    0, 0, 0, 1;
  
  y.matrix() << 
    cos(xzx[1] * M_PI / 180.0), 0, sin(xzx[1] * M_PI / 180.0), 0,
    0, 1, 0, 0,
    -sin(xzx[1] * M_PI / 180.0), 0, cos(xzx[1] * M_PI / 180.0), 0,
    0, 0, 0, 1;
  
  z.matrix() << 
    1, 0, 0, 0,
    0, cos(xzx[2] * M_PI / 180.0), -sin(xzx[2] * M_PI / 180.0), 0,
    0, sin(xzx[2] * M_PI / 180.0), cos(xzx[2] * M_PI / 180.0), 0,
    0, 0, 0, 1;
  
  return z*y*x;
}

#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  Eigen::RowVector3d ray_dir = ray.direction;
  Eigen::RowVector3d ray_source = ray.origin;

  Eigen::RowVector3d AB = A-B;
  Eigen::RowVector3d AC = A-C;
  Eigen::RowVector3d AE = A-ray_source;

  double a = AB[0];
  double b = AB[1];
  double c = AB[2];
  double d = AC[0];
  double e = AC[1];
  double f = AC[2]; 
  double g = ray_dir[0];
  double h = ray_dir[1];
  double i = ray_dir[2];
  double j = AE[0];
  double k = AE[1];
  double l = AE[2];
  
  double M = a * (e*i - h*f) + b * (g*f - d*i) + c * (d*h - e*g);

  // algorithm from text book P79
  t = -(f * (a*k - j*b) + e * (j*c - a*l) + d * (b*l - k*c)) / M;
  double sigma = (i * (a*k - j*b) + h * (j*c - a*l) + g * (b*l - k*c)) / M;
  double beta = (j * (e*i - h*f) + k * (g*f - d*i) + l * (d*h - e*g)) / M;
   
  if(t<min_t||t>max_t) return false;

  if(sigma<0 || sigma>1) return false;
  
  if(beta<0 || beta>1-sigma) return false;
  
  return true;

}

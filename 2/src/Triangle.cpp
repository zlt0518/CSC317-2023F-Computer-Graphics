#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>
#include <Eigen/Dense>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  Eigen::Vector3d ray_dir = ray.direction;
  Eigen::Vector3d ray_source = ray.origin;

  Eigen::Vector3d AB = std::get<0>(corners) - std::get<1>(corners);
  Eigen::Vector3d AC = std::get<0>(corners) - std::get<2>(corners);
  Eigen::Vector3d AE = std::get<0>(corners) - ray_source;

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


  //algorithm from text book P79
  t = -(f * (a*k - j*b) + e * (j*c - a*l) + d * (b*l - k*c)) / M;
   
  if(t<min_t) return false;

  double sigma = (i * (a*k - j*b) + h * (j*c - a*l) + g * (b*l - k*c)) / M;

  if(sigma<0 || sigma>1) return false;

  double beta = (j * (e*i - h*f) + k * (g*f - d*i) + l * (d*h - e*g)) / M;
  
  if(beta<0 || beta>1-sigma) return false;
  
  n = (std::get<1>(corners) - std::get<0>(corners)).cross(std::get<2>(corners) - std::get<0>(corners)).normalized();
  return true;

}
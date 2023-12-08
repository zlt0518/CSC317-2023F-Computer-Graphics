#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  Eigen::Vector3d ray_dir = ray.direction;
  Eigen::Vector3d ray_source = ray.origin;

  if(ray_dir.dot(normal)==0)
  {
    return false;
  }
  else

  t = - normal.dot(ray_source - point) / (ray_dir.dot(normal));

  if(t < min_t) return false;

  n = normal.normalized();

  return true;

}


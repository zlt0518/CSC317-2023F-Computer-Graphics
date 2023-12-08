#include "Sphere.h"
#include "Ray.h"

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  Eigen::Vector3d ray_dir = ray.direction;
  Eigen::Vector3d ray_source = ray.origin;

  double a = ray_dir.dot(ray_dir);
  double b = 2*ray_dir.dot(ray_source-center);
  double c = (ray_source-center).dot(ray_source-center)-pow(radius,2);

  double delta = pow(b,2)-4*a*c;

  if(delta < 0)
  {
    return false;
  }
  else if (delta == 0)
  {
    //have 1 answer
    t = (-b) / (2*a);
    if (t<min_t) return false;
    else
    {
      n = (ray_source + t *ray_dir - center).normalized();
      return true;
    }
  }
  else
  {
    //have 2 answers
    double t1 = (-b - sqrt(delta)) / (2*a); 
    double t2 = (-b + sqrt(delta)) / (2*a);

    if(t1 < min_t&& t2<min_t)
    {
      return false;
    }
    else if (t1<min_t&&t2>min_t)
    {
      t = t2;
    }
    else if(t2<min_t&&t1>min_t)
    {
      t = t1;
    }
    else
    {
      t = std::min(t1,t2);
    }

    n = (ray_source + t * ray_dir - center).normalized();
    return true;    

  }
}


#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{

  //textbook CH 12.3.1
  double ray_orgin_x = ray.origin(0);
  double ray_orgin_y = ray.origin(1);
  double ray_orgin_z = ray.origin(2);

  double a_x = 1 / ray.direction(0);
  double a_y = 1 / ray.direction(1);
  double a_z = 1 / ray.direction(2);


  double x_min = box.min_corner(0);
  double y_min = box.min_corner(1);
  double z_min = box.min_corner(2);
  double x_max = box.max_corner(0);
  double y_max = box.max_corner(1);
  double z_max = box.max_corner(2);


  double t_x_min = a_x * (x_min-ray_orgin_x); 
  double t_x_max = a_x * (x_max-ray_orgin_x); 
  double t_y_min = a_y * (y_min-ray_orgin_y); 
  double t_y_max = a_y * (y_max-ray_orgin_y); 
  double t_z_min = a_z * (z_min-ray_orgin_z); 
  double t_z_max = a_z * (z_max-ray_orgin_z);

  if(a_x<0) std::swap(t_x_max,t_x_min);
  if(a_y<0) std::swap(t_y_max,t_y_min);
  if(a_z<0) std::swap(t_z_max,t_z_min);

  //then find max of mins and min of maxs
  double max_min_t = std::max({t_x_min, t_y_min, t_z_min});
  double min_max_t = std::min({t_x_max, t_y_max, t_z_max});

  // out of bounds
  if (min_max_t < min_t || max_min_t > max_t) return false;
  if (max_min_t < min_t || min_max_t > max_t) return false;

    // no intersection
  if (min_max_t >= max_min_t)
  {
    return true;
  } 
  else
  {
    return false;
  } 

}

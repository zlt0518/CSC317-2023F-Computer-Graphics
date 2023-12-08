#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  if(num_recursive_calls>10)
  {
    return false;
  }

  int hit_id_temp;
  double t_temp;
  Eigen::Vector3d normal_temp;
  Ray ray_reflected;
  Eigen::Vector3d rgb_new;
  bool hit_temp = first_hit(ray,min_t,objects,hit_id_temp,t_temp,normal_temp);  


  if(hit_temp)
  {
    rgb = blinn_phong_shading(ray,hit_id_temp,t_temp,normal_temp,objects,lights);

    ray_reflected.origin = ray.origin + t_temp* ray.direction;
    ray_reflected.direction= (reflect(ray.direction,normal_temp));

    bool raycolor_next = raycolor(ray_reflected,0.000001,objects,lights,num_recursive_calls+1,rgb_new);
    if(raycolor_next)
    {
       rgb += (((rgb_new.array()) * ((objects[hit_id_temp]->material->km).array())).matrix());
    }

    
  }
  return hit_temp;

}


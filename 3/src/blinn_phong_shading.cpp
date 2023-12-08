#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{ 
  // relevant paramenters for blinn-phong
  Eigen::Vector3d color = 0.1 * (objects[hit_id]->material->ka); 
  Eigen::Vector3d k_diffuse = objects[hit_id]->material->kd; 
  Eigen::Vector3d k_specular = objects[hit_id]->material->ks;
  double p_exp = objects[hit_id]->material->phong_exponent;

  //construct light vector
  Eigen::Vector3d light_intersect = ray.origin + ray.direction * t;
  Ray shadow;
  shadow.origin = light_intersect;

    
  for(int i = 0; i < lights.size();i++)
  {
    double t_light_temp;
    lights[i]->direction(light_intersect,shadow.direction,t_light_temp);

    Eigen::Vector3d H = (-ray.direction.normalized() + shadow.direction).normalized();
    Eigen::Vector3d light_color = lights[i]->I;

    int hit_id_temp;
    double t_temp;
    Eigen::Vector3d normal_temp;

    
    bool hit_temp = first_hit(shadow,1e-6,objects,hit_id_temp,t_temp,normal_temp);
    if(!hit_temp||t_temp>t_light_temp)
    {
      //diffuse
      color += fmax(0.0, n.dot(shadow.direction)) *  (light_color.array() * k_diffuse.array()) .matrix();

      //specular
      color += pow(fmax(0.0, n.dot(H)),p_exp) * (light_color.array() * k_specular.array()) .matrix();

    }
  }

  return color;

}

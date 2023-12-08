#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  //orgin
  ray.origin = camera.e;

  //u and v
  double u_val = -(camera.width / 2.0) + camera.width * (j + 0.5) / width;
  double v_val = (camera.height / 2.0) - camera.height * (i + 0.5) / height;
  
  ray.direction = Eigen::Vector3d(u_val * camera.u + v_val * camera.v - camera.d * camera.w);

}

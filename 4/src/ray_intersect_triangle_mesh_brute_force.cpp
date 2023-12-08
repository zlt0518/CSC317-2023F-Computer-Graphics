#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  double minimum_t = std::numeric_limits<double>::infinity();
  int minimum_f;
  bool hit = false;

  if (F.rows() == 0) return false;
  
  Eigen::RowVector3d A = V.row(F(0,0));;
  Eigen::RowVector3d B = V.row(F(0,1));;
  Eigen::RowVector3d C = V.row(F(0,2));;

  for (int f = 1; f < F.rows(); f ++){
    A = V.row(F(f,0));
    B = V.row(F(f,1));
    C = V.row(F(f,2));

    double t_temp;

    bool hit_triangle = ray_intersect_triangle(ray,A,B,C,min_t,max_t,t_temp);

    if(hit_triangle && t_temp<minimum_t)
    {
      minimum_t = t_temp;
      minimum_f = f;
      hit = true;

    }
  }

  hit_t = minimum_t;
  hit_f = minimum_f;
  return hit;
}


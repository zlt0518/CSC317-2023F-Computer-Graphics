#include "triangle_triangle_intersection.h"
#include "ray_intersect_triangle.h"
#include "Ray.h"


bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  // usingh the two point of the triangle as ray and intersect with other triangle

  Ray A0A1(A0,A1-A0);
  Ray A0A2(A0,A2-A0);
  Ray A1A2(A1,A2-A1);
  Ray B0B1(B0,B1-B0);
  Ray B0B2(B0,B2-B0);
  Ray B1B2(B1,B2-B1);

  double temp_t = 0;

  if(ray_intersect_triangle(A0A1,B0,B1,B2,0,1,temp_t)||
     ray_intersect_triangle(A0A2,B0,B1,B2,0,1,temp_t)||
     ray_intersect_triangle(A1A2,B0,B1,B2,0,1,temp_t)||
     ray_intersect_triangle(B0B1,A0,A1,A2,0,1,temp_t)||
     ray_intersect_triangle(B0B2,A0,A1,A2,0,1,temp_t)||
     ray_intersect_triangle(B1B2,A0,A1,A2,0,1,temp_t)
    )
  {
    return true;
  }

  return false;

}
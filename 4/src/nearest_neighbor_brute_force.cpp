#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  if(points.rows() == 0) return;
  
  double min_distance = (points.row(0) - query).squaredNorm();
  int min_I = 0;

  for(int i = 1; i < points.rows();i++)
  {
    double temp_distance = (points.row(i) - query).squaredNorm();
    if(temp_distance < min_distance)
    {
      min_distance = temp_distance;
      min_I = i;
    }
  } 

  I = min_I;
  sqrD = min_distance;

}

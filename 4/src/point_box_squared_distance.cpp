#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  double distance = 0;

  double distance_x = std::max( { query(0) - box.max_corner(0), box.min_corner(0) - query(0) } );
  double distance_y = std::max( { query(1) - box.max_corner(1), box.min_corner(1) - query(1) } );
  double distance_z = std::max( { query(2) - box.max_corner(2), box.min_corner(2) - query(2) } );

  if(distance_x>0) distance += pow(distance_x,2);
  if(distance_y>0) distance += pow(distance_y,2);
  if(distance_z>0) distance += pow(distance_z,2);

  return distance;

}

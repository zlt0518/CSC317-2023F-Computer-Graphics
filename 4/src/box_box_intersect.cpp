#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  if (B.min_corner(0) > A.max_corner(0)||B.max_corner(0) < A.min_corner(0)) return false;
  if (B.min_corner(1) > A.max_corner(1)||B.max_corner(1) < A.min_corner(1)) return false;  
  if (B.min_corner(2) > A.max_corner(2)||B.max_corner(2) < A.min_corner(2)) return false;
  
  return true;
}

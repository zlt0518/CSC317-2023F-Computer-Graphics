#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{

  double smallest_t = std::numeric_limits<double>::max();
  int hit_num = 0;

  //loop throuh all the object
  for(int i = 0;i<objects.size();i++)
  {
    double t_curr;
    Eigen::Vector3d n_curr;

    bool hit_curr = objects[i]->intersect( ray, min_t, t_curr,  n_curr);

    if(hit_curr == true)
    {
      hit_num++;

      if (t_curr<smallest_t) 
      {
        hit_id = i;
        t = t_curr;
        n = n_curr;
        smallest_t = t_curr;
      }
    }

  }

  if (hit_num>0) 
  {
    return true;
  }
  else
  { 
    return false;
  }
}

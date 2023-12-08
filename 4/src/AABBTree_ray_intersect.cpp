#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  bool hit_box = ray_intersect_box(ray,box,min_t,max_t);

  if(!hit_box)
  {
    descendant = nullptr;
    return false;
  }

  double t_left;
  double t_right;
  bool left_hit = false;
  bool right_hit = false;

  std::shared_ptr<Object> left_descendant = left;
  std::shared_ptr<Object> right_descendant = right;

  if(left)
  {
    left_hit = left->ray_intersect(ray, min_t, max_t,t_left, left_descendant);
  }
  if(right)
  {   
    right_hit = right->ray_intersect(ray, min_t, max_t,t_right, right_descendant);
  }

  if (!left_hit && !right_hit) 
  {
    descendant = nullptr;
    return false;
  }
  else 
  {
    //when actual hit with an object
    if(!left_descendant && left_hit){
      left_descendant = left;
    }
    if(!right_descendant && right_hit){
      right_descendant = right;
    }

    if (left_hit && right_hit) {
      t = fmin(t_left, t_right);

      if(t_left <= t_right){
        descendant = left_descendant;
      }else{
        descendant = right_descendant;
      }

      return true;

    } 
    else if (right_hit) 
    {
        t = t_right;
        descendant = right_descendant;
        return true;
    } 
    else if(left_hit)
    {
        t = t_left;
        descendant = left_descendant;
        return true;
    }
    else
    {
      return false;
    }

    
  }

  return false;
}


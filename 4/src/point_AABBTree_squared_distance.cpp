#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  double minimum_distance = std::numeric_limits<double>::infinity();

  std::priority_queue< std::pair<double, std::shared_ptr<Object> >
                      ,std::vector<std::pair<double, std::shared_ptr<Object> > >, 
                      std::greater<std::pair<double, std::shared_ptr<Object> > > >  distance_queue; 


  double root_distance = point_box_squared_distance(query, root->box);
  distance_queue.push(std::make_pair(root_distance,root));

  while(!distance_queue.empty())
  {
    std::pair<double, std::shared_ptr<Object> > distance_pair_curr = distance_queue.top();
    
    distance_queue.pop();

    double distance_curr = distance_pair_curr.first;

    if(distance_curr<minimum_distance)
    {
      std::shared_ptr<Object>  object_curr = distance_pair_curr.second;
      std::shared_ptr<AABBTree> tree_curr = std::dynamic_pointer_cast<AABBTree>(object_curr);

      if(!tree_curr)
      {
        //leaf
        minimum_distance = distance_curr;
        descendant = object_curr;        
      }
      else
      {
        //non leaf
        double point_tree_distance_curr;

        //left side
        if(tree_curr->left)
        {
          point_tree_distance_curr = point_box_squared_distance(query, tree_curr->left->box);

          distance_queue.push(std::make_pair(point_tree_distance_curr,tree_curr->left));
        }

        //right side
        if(tree_curr->right)
        {
          point_tree_distance_curr = point_box_squared_distance(query, tree_curr->right->box);

          distance_queue.push(std::make_pair(point_tree_distance_curr,tree_curr->right));
        }   
      }
    }
  }
  
  sqrd = minimum_distance;
  return (min_sqrd <= sqrd && sqrd <= max_sqrd);
}

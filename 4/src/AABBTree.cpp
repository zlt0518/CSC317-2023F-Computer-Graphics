#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  
  if(num_leaves == 0)
  {
    left = nullptr;
    right = nullptr;
    return;
  } 
  else if(num_leaves == 1)
  {
    left = objects[0];
    insert_box_into_box(objects[0]->box, box);
    right = nullptr;
    return;
  }
  else if(num_leaves == 2)
  {
    left = objects[0];
    insert_box_into_box(objects[0]->box, box);
    right = objects[1];
    insert_box_into_box(objects[1]->box, box);
    return;
  }
  else
  {
    //insert in all boxes of these objects 
    for(int i = 0;i < num_leaves;i++){
      insert_box_into_box(objects[i]->box, box); 
    }

    //more leaves
    std::vector<std::shared_ptr<Object> > left_objects;
    std::vector<std::shared_ptr<Object> > right_objects;

    double x_length = box.max_corner(0) - box.min_corner(0);
    double y_length = box.max_corner(1) - box.min_corner(1);
    double z_length = box.max_corner(2) - box.min_corner(2);

    double max_legth = std::max({x_length,y_length,z_length});

    int max_axis_index;

    if (max_legth == x_length)
    {
      max_axis_index = 0;      
    }
    else if(max_legth == y_length)
    {
      max_axis_index = 1;  
    }
    else if (max_legth == z_length)
    {
      max_axis_index = 2;
    }

    for(int i = 0; i<num_leaves;i++)
    {
      if (objects[i]->box.center()(max_axis_index) <= box.center()(max_axis_index))
      {
        left_objects.push_back(objects[i]);
      } 
      else
      {
        right_objects.push_back(objects[i]);
      }      
    }

    
    //check unblance of the tree
    if(left_objects.empty())
    {
      left_objects.push_back(right_objects.back());
      right_objects.pop_back();
    }
    else if(right_objects.empty())
    {
      right_objects.push_back(left_objects.back());
      left_objects.pop_back();      
    }
    
    // recursive calling constructor
    left = std::make_shared<AABBTree>(left_objects, depth+1);
    right = std::make_shared<AABBTree>(right_objects, depth+1);

  }

}


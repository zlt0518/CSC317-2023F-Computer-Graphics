#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object> > > box_queue;

  if(!box_box_intersect(rootA->box, rootB->box)) return;

  box_queue.push_back(std::make_pair(rootA,rootB));

  while(!box_queue.empty())
  {
    std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > node_pair = box_queue.front();
    std::shared_ptr<Object> nodeA_temp = node_pair.first;
    std::shared_ptr<Object> nodeB_temp = node_pair.second;
    box_queue.pop_front();

    std::shared_ptr<AABBTree> nodeA_tree_temp = std::dynamic_pointer_cast<AABBTree> (nodeA_temp);
    std::shared_ptr<AABBTree> nodeB_tree_temp = std::dynamic_pointer_cast<AABBTree> (nodeB_temp);
    
    //both are leaves
    if(nodeA_tree_temp == nullptr && nodeB_tree_temp == nullptr) 
    {
      //both leaves
      if(box_box_intersect(nodeA_temp->box,nodeB_temp->box))  
      {
        leaf_pairs.push_back(node_pair);
      }
    }
    else if (nodeA_tree_temp == nullptr && nodeB_tree_temp != nullptr)
    {
      //A leaf, B not leaf
      //bl
      if(nodeB_tree_temp->left && box_box_intersect(nodeA_temp->box,nodeB_tree_temp->left->box))
      {
        box_queue.push_back(std::make_pair(nodeA_temp,nodeB_tree_temp->left));
      }
      //br
      if(nodeB_tree_temp->right && box_box_intersect(nodeA_temp->box,nodeB_tree_temp->right->box))
      {
        box_queue.push_back(std::make_pair(nodeA_temp,nodeB_tree_temp->right));
      }
    }
    else if (nodeA_tree_temp != nullptr && nodeB_tree_temp == nullptr)
    {
      //A not leaf, B leaf
      //al
      if(nodeA_tree_temp->left && box_box_intersect(nodeA_tree_temp->left->box,nodeB_temp->box))
      {
        box_queue.push_back(std::make_pair(nodeA_tree_temp->left,nodeB_temp));
      }
      //ar
      if(nodeA_tree_temp->right && box_box_intersect(nodeA_tree_temp->right->box,nodeB_temp->box))
      {
        box_queue.push_back(std::make_pair(nodeA_tree_temp->right,nodeB_temp));
      }
    } 
    else
    {
      //all non leaves
      
      if(nodeA_tree_temp->left && nodeB_tree_temp->left)
      {
        //al-bl
        if(box_box_intersect(nodeA_tree_temp->left->box,nodeB_tree_temp->left->box))
        {
          box_queue.push_back(std::make_pair(nodeA_tree_temp->left,nodeB_tree_temp->left));
        }
      }

      if(nodeA_tree_temp->left && nodeB_tree_temp->right)
      {
        //al-br
        if(box_box_intersect(nodeA_tree_temp->left->box,nodeB_tree_temp->right->box))
        {
          box_queue.push_back(std::make_pair(nodeA_tree_temp->left,nodeB_tree_temp->right));
        }
      }
      if(nodeA_tree_temp->right && nodeB_tree_temp->left)
      {
        //ar-bl
        if(box_box_intersect(nodeA_tree_temp->right->box,nodeB_tree_temp->left->box))
        {
          box_queue.push_back(std::make_pair(nodeA_tree_temp->right,nodeB_tree_temp->left));
        }
      }

      if(nodeA_tree_temp->right && nodeB_tree_temp->right)
      {
        //ar-ar
        if(box_box_intersect(nodeA_tree_temp->right->box,nodeB_tree_temp->right->box))
        {
          box_queue.push_back(std::make_pair(nodeA_tree_temp->right,nodeB_tree_temp->right));
        }
      }    
    }   
  }
}
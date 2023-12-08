#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>
#include "vertex_triangle_adjacency.h"

  /*
  Note:
  I could not finish this task, and neither did most of my classmates.The average for this assignment is much lower than other assignments (~87%), and I still managed to receive 90.5% for this assignment.
  so it its ok! Don't worry about this part.
  It is not worth wasting your time on this part. 
  */


void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
  //base case
  if(num_iters == 0) return;

  std::vector<std::vector<int> > VF;
  vertex_triangle_adjacency(F, V.rows(), VF);

  std::vector<Eigen::RowVector3d> surface_midpoint_list; //face is the key
  std::vector<Eigen::RowVector3d> new_vertices_list; //face is the key
  std::vector<Eigen::RowVector3d> new_edge_midpoint_list;

  std::vector<std::vector<Eigen::RowVector3d>> face_Edge_Midpoint_list;

  std::vector<std::vector<Eigen::RowVector3d>> vertex_edge_list;

  face_Edge_Midpoint_list.resize(F.rows());
  vertex_edge_list.resize(V.rows());
  new_vertices_list.resize(V.rows());

  //face poi

  for(int i = 0; i<F.rows();i++)
  {
      Eigen::RowVector3d a  = V.row(F(i,0));
      Eigen::RowVector3d b  = V.row(F(i,1));
      Eigen::RowVector3d c  = V.row(F(i,2));
      Eigen::RowVector3d d  = V.row(F(i,3));

      surface_midpoint_list[i] = (a+b+c+d)/4;
  }

  //edge mid point
  for(int i = 0;i<F.rows();i++)
  {

    for(int j = 0;j<F.cols(); j++)
    {
      //two adjacant vertices j and j+1
      int j_mod = (j+1)%(F.cols());
      Eigen::RowVector3d v_a = V.row(F(i,j));
      Eigen::RowVector3d v_b = V.row(F(i,j_mod));

      //list of neighbour faces
      std::vector<int> v_a_neighbour = VF[F(i,j)];
      std::vector<int> v_b_neighbour = VF[F(i,j_mod)];    

      std::vector<int> v_a_b_faces;

      //find common faces
      std::set_intersection(v_a_neighbour.begin(), v_a_neighbour.end(), v_b_neighbour.begin(), v_b_neighbour.end(), std::back_inserter(v_a_b_faces)); 

      Eigen::RowVector3d edge_mid;
      //do not set up if there are no two faces connection
      if(v_a_b_faces.size() ==2)
      {
        edge_mid = (surface_midpoint_list[v_a_b_faces[0]] + surface_midpoint_list[v_a_b_faces[1]]+v_a+v_b);
      }
      else if(v_a_b_faces.size() ==1)
      {
        //should not happen but just in case
        edge_mid = (surface_midpoint_list[v_a_b_faces[0]] +v_a+v_b);
      }
      else
      {
        continue;
      }

      //add to edge midpoit 
      face_Edge_Midpoint_list[i].push_back(edge_mid);
      new_edge_midpoint_list.push_back(edge_mid);
      vertex_edge_list[F(i,j)].push_back(edge_mid);

    }
  }

  // calculate new vertex point 
  for(int i = 0; i <V.rows();i++)
  {
    //R
    Eigen::RowVector3d R_curr(0, 0, 0);

    for(int j = 0;j<vertex_edge_list[i].size(); j++)
    {
      R_curr+=vertex_edge_list[i][j];
    }  

    R_curr/= vertex_edge_list[i].size();  

    //F
    Eigen::RowVector3d F_curr(0, 0, 0);

    for(int j = 0;j<VF[i].size(); j++)
    {
      F_curr+=surface_midpoint_list[VF[i][j]];
    }

    F_curr/= VF[i].size();


    //n
    int n_curr = vertex_edge_list[i].size() + VF[i].size();

    // P = V.rows(i) 
    Eigen::RowVector3d P_curr = (F_curr+ 2*R_curr + (n_curr-3)* V.row(i)) /n_curr;

    new_vertices_list[i] = P_curr;
  }

  SV.resize(surface_midpoint_list.size()+new_vertices_list.size()+new_edge_midpoint_list.size(),4);

  //NEED TO CONNECT 
  




}

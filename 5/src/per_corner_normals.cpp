#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  
  std::vector<std::vector<int> > VF;
  vertex_triangle_adjacency(F, V.rows(), VF);

  double threshold_val = cos(corner_threshold / 180 * M_PI);

   for(int i = 0;i < F.rows();i++)
   {

    Eigen::RowVector3d norm_reference = triangle_area_normal( V.row(F(i,0)), V.row(F(i,1)), V.row(F(i,2)) );

    for(int j = 0; j < F.cols();j++)
    {
      std::vector<int> neighbors_curr = VF[F(i,j)]; 

      for(int k = 0;k < neighbors_curr.size();k++)
      {
        Eigen::RowVector3d a  = V.row(F(neighbors_curr[k], 0));
        Eigen::RowVector3d b  = V.row(F(neighbors_curr[k], 1));
        Eigen::RowVector3d c  = V.row(F(neighbors_curr[k], 2)); 

        Eigen::RowVector3d norm_curr = triangle_area_normal(a,b,c);

        if(norm_curr.normalized().dot(norm_reference.normalized()) > threshold_val)
        {
          N(3 * i + j, 0) += norm_curr(0);
          N(3 * i + j, 1) += norm_curr(1);
          N(3 * i + j, 2) += norm_curr(2);
        } 

      }
      
      N.row(3 * i + j).normalized();

    }  

   } 

}


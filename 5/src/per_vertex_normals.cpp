#include "per_vertex_normals.h"
#include "triangle_area_normal.h"
#include "vertex_triangle_adjacency.h"

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);
  std::vector<std::vector<int> > VF;

  vertex_triangle_adjacency(F, V.rows(), VF);

  for(int i = 0;i<V.rows();i++)
  {

    Eigen::RowVector3d total_normal(0, 0, 0);

    for (int j = 0; j < VF[i].size(); j++)
    {
      Eigen::RowVector3d a  = V.row(F(VF[i][j],0) );
      Eigen::RowVector3d b  = V.row(F(VF[i][j],1) );
      Eigen::RowVector3d c  = V.row(F(VF[i][j],2) );

      total_normal += triangle_area_normal(a,b,c);
    
    } 
    //normalized
    N.row(i) = total_normal.normalized();
  }

}


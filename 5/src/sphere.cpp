#include "sphere.h"
#include <iostream>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{

  int face_num = num_faces_u * num_faces_v;
  int vertex_num = (num_faces_v + 1) * (num_faces_u + 1);  

  //change the size
  V.resize(vertex_num, 3);
  F.resize(face_num,4);
  UV.resize(vertex_num,2);
  UF.resize(face_num,4);
  NV.resize(vertex_num,3);
  NF.resize(face_num,4);  

  int index_V = 0;
  int index_F = 0;

  for(int i = 0;i <= num_faces_v;i++)
  {
    for(int j = 0;j <= num_faces_u;j++)
    {  
      V(index_V, 0) = sin(i*M_PI / num_faces_v)* sin(j * (2*M_PI) / num_faces_u);         
      V(index_V, 1) = cos(i*M_PI / num_faces_v);   
      V(index_V, 2) = sin(i*M_PI / num_faces_v)* cos(j * (2*M_PI) / num_faces_u) ;

      NV(index_V, 0) = V(index_V, 0);  
      NV(index_V, 1) = V(index_V, 1);  
      NV(index_V, 2) = V(index_V, 2);  
    
      UV(index_V, 0) =  j *( 1.0 / (num_faces_u+1));
      UV(index_V, 1) =  (num_faces_v + 1 - i) * (1.0/ (num_faces_v + 1));

      index_V++;

      if(i == num_faces_v||j ==num_faces_u) continue;

      int vertex_upleft = i * (num_faces_u + 1) + j;
      int vertex_upright = i * (num_faces_u + 1) + j + 1;
      int vertex_downright = (i + 1) * (num_faces_u + 1) + j + 1;
      int vertex_downleft = (i + 1) * (num_faces_u + 1) + j;

      F.row(index_F) =  Eigen::RowVector4i(vertex_upleft, vertex_upright, vertex_downright, vertex_downleft);
      NF.row(index_F) =  F.row(index_F);
      UF.row(index_F) = F.row(index_F);

      index_F++;
      
    }

    
  }      

}

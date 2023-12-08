#include "cube.h"

void cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{

  ////Hint:
  V.resize(8,3);
  V.row(0) = Eigen::RowVector3d( 0, 0, 0 );
  V.row(1) = Eigen::RowVector3d( 0, 1, 0 );
  V.row(2) = Eigen::RowVector3d( 1, 1, 0 );
  V.row(3) = Eigen::RowVector3d( 1, 0, 0 );
  V.row(4) = Eigen::RowVector3d( 0, 0, 1 );
  V.row(5) = Eigen::RowVector3d( 0, 1, 1 );
  V.row(6) = Eigen::RowVector3d( 1, 1, 1 );
  V.row(7) = Eigen::RowVector3d( 1, 0, 1 );

  F.resize(6,4);
  F.row(0) = Eigen::Vector4i(0, 1, 2, 3); 
  F.row(1) = Eigen::Vector4i(2, 3, 7, 6); 
  F.row(2) = Eigen::Vector4i(4, 5, 6, 7); 
  F.row(3) = Eigen::Vector4i(0, 4, 5, 1);
  F.row(4) = Eigen::Vector4i(0, 4, 7, 3); 
  F.row(5) = Eigen::Vector4i(1, 5, 6, 2);

  UV.resize(14,2);
  UV.row(0) = Eigen::RowVector2d(0.25, 0);
  UV.row(1) = Eigen::RowVector2d(0.5, 0);
  UV.row(2) = Eigen::RowVector2d(0, 0.25);
  UV.row(3) = Eigen::RowVector2d(0.25, 0.25);
  UV.row(4) = Eigen::RowVector2d(0.5, 0.25);
  UV.row(5) = Eigen::RowVector2d(0.75, 0.25);
  UV.row(6) = Eigen::RowVector2d(1, 0.25 );
  UV.row(7) = Eigen::RowVector2d(0, 0.5);
  UV.row(8) = Eigen::RowVector2d(0.25, 0.5);
  UV.row(9) = Eigen::RowVector2d(0.5, 0.5);
  UV.row(10) = Eigen::RowVector2d(0.75, 0.5);
  UV.row(11) = Eigen::RowVector2d(1, 0.5);
  UV.row(12) = Eigen::RowVector2d(0.25, 0.75);
  UV.row(13) = Eigen::RowVector2d(0.5, 0.75);

  UF.resize(6,4);
  UF.row(0) = Eigen::Vector4i(3, 8, 9, 4); 
  UF.row(1) = Eigen::Vector4i(4, 9, 10, 5); 
  UF.row(2) = Eigen::Vector4i(5, 10, 11, 6); 
  UF.row(3) = Eigen::Vector4i(2, 7, 8, 3); 
  UF.row(4) = Eigen::Vector4i(8, 12, 13, 9); 
  UF.row(5) = Eigen::Vector4i(0, 3, 4, 1); 
  
  NV.resize(6,3);
  NV.row(0) = Eigen::RowVector3d(0, 0, -1);
  NV.row(1) = Eigen::RowVector3d(1, 0, 0);
  NV.row(2) = Eigen::RowVector3d(0, 0, 1);
  NV.row(3) = Eigen::RowVector3d(-1, 0, 0);
  NV.row(4) = Eigen::RowVector3d(0, -1, 0);
  NV.row(5) = Eigen::RowVector3d(0, 1, 0);

  NF.resize(6,4);
  NF.row(0) = Eigen::RowVector4i(0,0,0,0);
  NF.row(1) = Eigen::RowVector4i(1,1,1,1);
  NF.row(2) = Eigen::RowVector4i(2,2,2,2);
  NF.row(3) = Eigen::RowVector4i(3,3,3,3);
  NF.row(4) = Eigen::RowVector4i(4,4,4,4);
  NF.row(5) = Eigen::RowVector4i(5,5,5,5);
}

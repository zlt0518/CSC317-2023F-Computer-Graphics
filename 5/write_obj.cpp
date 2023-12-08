#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  

  std::ofstream outFile(filename);

  if (!outFile.is_open())
  {
    //error in opening the file
    return false;
  }

  //reference https://en.wikipedia.org/wiki/Wavefront_.obj_file
  outFile<<"# List of geometric vertices, with (x, y, z, [w]) coordinates, w is optional and defaults to 1.0."<<std::endl;
  
  for(int i = 0;i < V.rows();i++)
  {
    outFile<<"v "<<V(i, 0)<<" "<<V(i, 1)<<" "<<V(i, 2)<<std::endl;
  }

  outFile<<"# List of texture coordinates, in (u, [v, w]) coordinates, these will vary between 0 and 1. v, w are optional and default to 0."<<std::endl;
  
  for (int i = 0; i < UV.rows(); i++)
  {
    outFile << "vt " << UV(i, 0) << " " << UV(i, 1) << std::endl;
  }
  
  outFile<<"# List of vertex normals in (x,y,z) form; normals might not be unit vectors."<<std::endl;
  
  for(int i = 0;i < NV.rows();i++)
  {
    outFile<<"vn "<<NV(i, 0)<<" "<<NV(i, 1)<<" "<<NV(i, 2)<<std::endl;
  }

  outFile<<"# Polygonal face element (see below)"<<std::endl;

  for(int i = 0;i < F.rows();i++)
  {
    outFile<<"f ";

    for(int j = 0;j < F.cols();j++){

      outFile<<F(i, j)+1<<"/"<<UF(i, j)+1<<"/"<<NF(i, j)+1<<" ";
    }
    outFile<<std::endl;
    
  }


  outFile.close();


  return true;
}

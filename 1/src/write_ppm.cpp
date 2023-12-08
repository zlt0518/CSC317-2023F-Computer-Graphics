#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");

  std::ofstream outFile(filename);

  if (!outFile.is_open())
  {
    //error in opening the file
    return false;
  }

  if (num_channels == 3)
  {
    //rgb cases
    outFile<<"P3"<<std::endl;
    outFile<<width<<" "<<height<<std::endl;
    outFile<<255<<std::endl;    

    for (int i = 0; i<height;i++)
    {

      for(int j = 0;j<width;j++)
      {
        outFile<<(int)data[3*(j+i*width)]<<" "<<(int)data[3*(j+i*width)+1]<<" "<<(int)data[3*(j+i*width)+2];

        if(j+1 < width)
        {
          outFile<<"   ";
        }
      }
      
      outFile<<std::endl;
    }
    outFile.close();
    return true;
  }
  else if (num_channels == 1)
  {
    //grey cases
    outFile<<"P2"<<std::endl;
    outFile<<width<<" "<<height<<std::endl;
    outFile<<255<<std::endl;  
    
    for (int i = 0; i<height;i++)
    {

      for(int j = 0;j<width;j++)
      {
        outFile<<(int)data[j+i*width];

        if(j+1 < width)
        {
          outFile<<"   ";
        }
      }
      outFile<<std::endl;

    }

    outFile.close();
    return true;
  }

  else
  {
    return false;
  }

  return false;
}

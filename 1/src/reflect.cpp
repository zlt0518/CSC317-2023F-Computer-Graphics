#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i<height;i++)
  {
    for(int j = 0; j<width;j++)
    {
      for(int channel = 0;channel<num_channels; channel++)
      {
        reflected[i*width*num_channels+j*num_channels+channel] = input[i*width*num_channels+(width-1-j)*num_channels+channel];
      }

    }

  }  

}

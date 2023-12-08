#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////

  for (int i = 0; i<width;i++)
  {
    for(int j = 0; j<height;j++)
    {
      for(int channel = 0;channel<num_channels; channel++)
      {
        rotated[i*height*num_channels+j*num_channels+channel] = input[j*width*num_channels+(width-1-i)*num_channels+channel];
      }

    }

  }  

}

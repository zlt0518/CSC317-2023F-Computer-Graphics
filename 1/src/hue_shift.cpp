#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"
#include <cmath>

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());

  for (int i = 0; i<height;i++)
  {
    for(int j = 0; j<width;j++)
    {
      double r,g,b,h,s,v;
      r = rgb[i*width*3+j*3];
      g = rgb[i*width*3+j*3+1];
      b = rgb[i*width*3+j*3+2];

      rgb_to_hsv(r,g,b,h,s,v);
      
      h-=shift;
      
      if(h<0.0)
      {
        h = 360.0 - std::abs(h);
      }
      else if(h>360)
      {
        h -= 360;
      }

      hsv_to_rgb(h,s,v,r,g,b);
      shifted[i*width*3+j*3]   = r;
      shifted[i*width*3+j*3+1] = g;
      shifted[i*width*3+j*3+2] = b;

    }

  }    
}

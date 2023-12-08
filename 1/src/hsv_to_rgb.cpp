#include "hsv_to_rgb.h"
#include <cmath>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  if(s == 0.0)
  {
    r =0;
    g = 0;
    b = 0;
  }
  else
  {
    double s1 = s*v;
    double s2 = s1*(1.0-std::abs(std::fmod(h/60.0,2.0)-1.0));
    double s3 = v-s1;

    if(h>=0.0 && h<60.0)
    {
      r = s1;
      g = s2;
      b = 0;

    }
    else if(h>=60.0 && h<120.0)
    {
      r = s2;
      g = s1;
      b = 0;

    }
    else if(h>=120.0 &&h<180.0)
    {
      r = 0;
      g = s1;
      b = s2;
      
    }
    else if(h>=180.0 &&h<240.0)
    {
      r = 0;
      g = s2;
      b = s1;
      
    }
    else if(h>=240.0 &&h<300.0)
    {
      r = s2;
      g = 0;
      b = s1;
      
    }
    else if(h>=300.0 &&h<360.0)
    {
      r = s1;
      g = 0;
      b = s2;
      
    }

    r+=s3;
    g+=s3;
    b+=s3;

    r*=255.0;
    g*=255.0;
    b*=255.0;
    
  }
}

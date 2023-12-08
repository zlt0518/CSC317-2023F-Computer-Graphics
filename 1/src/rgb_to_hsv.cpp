#include "rgb_to_hsv.h"
#include <algorithm>

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  double r_val = r/255.0;
  double g_val = g/255.0;
  double b_val = b/255.0;

  double max = std::max({r_val,g_val,b_val});
  double min = std::min({r_val,g_val,b_val});
  double diff = max -min;

  //hue
  if(max==min)
  {
    h = 0.0;
  }
  else if(max==r_val)
  {
    if(g_val>=b_val)
    {
      h = 60.0 *(g_val-b_val)/(diff);
    }
    else
    {
      h = 60.0 *(g_val-b_val)/(diff)+360.0;
    }
  }
  else if(max == g_val)
  {
    h = 60.0 *(b_val-r_val)/(diff)+120.0;
  }
  else if(max == b_val)
  {
    h = 60.0 *(r_val-g_val)/(diff)+240.0;
  }
  
  //saturation
  if(max == 0)
  {
    s = 0;
  }
  else
  {
    s = diff/max;
  }

  //value
  v = max;

}

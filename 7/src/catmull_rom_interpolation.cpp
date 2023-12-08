#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{

  //reference: https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline
  if (keyframes.empty()) {
      return Eigen::Vector3d::Zero();
  }

  auto time = fmod(t, keyframes.back().first);

  int i = 0;
  while(i < keyframes.size())
  {
    if (time == keyframes[i].first) 
    {
      return keyframes[i].second; 
    }
    else if(time < keyframes[i].first)
    {
      i++;
    }
    else
    {
      //greater
      break;
    }

  }

  Eigen::Vector3d P0,P1,P2,P3;
  double t0, t1, t2, t3;
  if(i==0)
  {
    P0 = keyframes[i].second;
    t0 = keyframes[i].first;
  }
  else
  {
    P0 =keyframes[i-1].second;
    t0 =keyframes[i-1].first;
  }

  if(i==keyframes.size()-2)
  {
    P3 = keyframes[i+1].second;
    t3 = keyframes[i+1].first;
  }
  else
  {
    P3 =keyframes[i+2].second;
    t3 =keyframes[i+2].first;
  }


  P1 = keyframes[i].second;
  t1 = keyframes[i].first;
  P2 = keyframes[i + 1].second;
  t2 = keyframes[i + 1].first;

  
  Eigen::Vector3d A1, A2, A3, B1, B2, C;
  A1 = ((t1 - time) / (t1 - t0)) * P0 + ((time - t0) / (t1 - t0)) * P1;
  A2 = ((t2 - time) / (t2 - t1)) * P1 + ((time - t1) / (t2 - t1)) * P2;
  A3 = ((t3 - time) / (t3 - t2)) * P2 + ((time - t2) / (t3 - t2)) * P3;
  B1 = ((t2 - time) / (t2 - t0)) * A1 + ((time - t0) / (t2 - t0)) * A2;
  B2 = ((t3 - time) / (t3 - t1)) * A2 + ((time - t1) / (t3 - t1)) * A3;
  C =  ((t2 - time) / (t2 - t1)) * B1 + ((time - t1) / (t2 - t1)) * B2;

  return C;
}


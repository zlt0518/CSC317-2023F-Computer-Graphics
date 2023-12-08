#include "line_search.h"
#include <iostream>

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
  auto alpha = max_step;
  auto f0 = f(z);
  Eigen::VectorXd z_ls;
  while(alpha > 1e-4)
  {
    z_ls = z - alpha *dz;
    proj_z(z_ls);
    auto f_ls = f(z_ls);

    if(f_ls<f0)
    {
      return alpha;
    }
    
    alpha*=0.5;
  }

  return alpha;
}


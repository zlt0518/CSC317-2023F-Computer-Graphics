#include "projected_gradient_descent.h"
#include "line_search.h"

void projected_gradient_descent(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const int max_iters,
  Eigen::VectorXd & z)
{
  double max_step = 30000.0;
  Eigen::VectorXd gradient;

  for (int iters=0; iters<max_iters; ++iters) {
    Eigen::VectorXd dz = grad_f(z);
    
    gradient = grad_f(z); 
    z = z - line_search(f, proj_z, z, gradient, max_step) * gradient;
    proj_z(z);
  }
}

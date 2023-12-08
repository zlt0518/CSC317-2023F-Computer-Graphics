#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  return  (in - 2 * (in.dot(n)) * n).normalized();
}


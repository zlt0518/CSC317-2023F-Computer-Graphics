#include "fast_mass_springs_step_dense.h"
#include <igl/matlab_format.h>

void fast_mass_springs_step_dense(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXi & b,
  const double delta_t,
  const Eigen::MatrixXd & fext,
  const Eigen::VectorXd & r,
  const Eigen::MatrixXd & M,
  const Eigen::MatrixXd & A,
  const Eigen::MatrixXd & C,
  const Eigen::LLT<Eigen::MatrixXd> & prefactorization,
  const Eigen::MatrixXd & Uprev,
  const Eigen::MatrixXd & Ucur,
  Eigen::MatrixXd & Unext)
{
  Eigen::MatrixXd d = Eigen::MatrixXd::Zero(E.rows(), 3);
  Unext.resize(Ucur.rows(), Ucur.cols());
  
  //global step
  for(int i = 0;i < 50;i++)
  {
    Eigen::MatrixXd l = Eigen::MatrixXd::Zero(V.rows(), 3);

    //local step
    for (int j = 0; j < E.rows(); j++) {
      d.row(j) = (Unext.row(E(j, 0)) - Unext.row(E(j, 1))).normalized() * r[j];
    }
      // b = kAᵀd + y + wCᵀC * p_rest 
      l = k * A.transpose() * d + M * (2 * Ucur - Uprev) / pow(delta_t, 2) + fext + 1e10 * C.transpose() * C * V;
      Unext = prefactorization.solve(l);
  }

}

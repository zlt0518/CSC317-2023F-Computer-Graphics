#include "fast_mass_springs_precomputation_sparse.h"
#include "signed_incidence_matrix_sparse.h"
#include <vector>

bool fast_mass_springs_precomputation_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::SparseMatrix<double>  & M,
  Eigen::SparseMatrix<double>  & A,
  Eigen::SparseMatrix<double>  & C,
  Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization)
{
    //mass matrix(diagonal)
  std::vector<Eigen::Triplet<double> > ijv;
  //edge lengths
  r.resize(E.rows());
  for(int i = 0;i < E.rows();i++){
    Eigen::VectorXd v0 =  V.row(E(i, 0));
    Eigen::VectorXd v1 =  V.row(E(i, 1));
    auto edge = v0 - v1;
    r[i] = edge.norm();
  }

 // mass matrix
  M.resize(V.rows(), V.rows());
  for(int i = 0;i < V.rows();i++){
    ijv.emplace_back(i, i, m[i]);
  }
  M.setFromTriplets(ijv.begin(), ijv.end());

  ijv.clear();


  //signed indices matrix_dense
  signed_incidence_matrix_sparse(V.rows(), E, A);


  //selection matrix
  C.resize(b.size(), V.rows());
  for(int i = 0;i < b.size();i++){
    //C(i, b[i]) = 1;
    ijv.emplace_back(i, b[i], 1);
  }
  C.setFromTriplets(ijv.begin(), ijv.end());
  ijv.clear();

  //Q = kA^TA + 1/delta_t^2 * M + extra term
  Eigen::SparseMatrix<double> Q( V.rows(), V.rows());
  Q = k * A.transpose() * A + 1 / pow(delta_t, 2) * M + 1e10 * C.transpose() * C;
  prefactorization.compute(Q);

  return prefactorization.info() != Eigen::NumericalIssue;
}

#include "TheFiniteElementMethod/05_improved_bar_element.h"


ImprovedBarElement::ImprovedBarElement()
{
}

ImprovedBarElement::~ImprovedBarElement()
{

}

void ImprovedBarElement::ReduceDimention(const int& dof, MatrixXd& M)
{
  // M.block(dof, 0, M.rows() - 1, M.cols()) = M.bottomRows(M.rows() - 1);
  // M.block(0, dof, M.rows(), M.cols() - 1) = M.rightCols(M.cols() - 1);
  // M.conservativeResize(M.rows() - 1, M.cols() - 1);
  EigenUtils::RemoveRow(M, M.rows() - 1);
  EigenUtils::RemoveColumn(M, M.cols() - 1);
}

std::tuple<MatrixXd, MatrixXd, VectorXd, MatrixXd> ImprovedBarElement::Bar(const int num_elems)
{
  MatrixXd m, k;
  m.resize(3, 3);
  k.resize(3, 3);
  
  m <<  4,  2, -1,
        2, 16,  2,
       -1,  2,  4;

  k <<  7, -8,  1,
       -8, 16, -8,
        1, -8,  7;


  // element mass and stiffness matrices for a bar 
  m /= (30.0 * static_cast<double>(num_elems));
  k *= (1.0 / 3.0) * static_cast<double>(num_elems);

  // construct global mass and stiffness matrices
  MatrixXd M = MatrixXd::Zero(2 * num_elems + 1, 2 * num_elems + 1);
  MatrixXd K = MatrixXd::Zero(2 * num_elems + 1, 2 * num_elems + 1);

  // Assembly of elements
  for (int i = 0; i < num_elems; ++i)
  {
    int first_node = 2 * i;
    M.block(first_node, first_node, 3, 3) += m;
    K.block(first_node, first_node, 3, 3) += k;
  }

  // Restrained degrees of freedom
  std::vector<int> restrained_dofs = {0};
  for(int dof : restrained_dofs)
  {
    ReduceDimention(dof, M);
    ReduceDimention(dof, K);
  }

  // Eigenvalue problem: Solve the generalized eigenvalue problem
  Eigen::GeneralizedSelfAdjointEigenSolver<MatrixXd> es(K, M);
  VectorXd evals = es.eigenvalues();
  MatrixXd evecs = es.eigenvectors();

  // Calculate frequencies
  VectorXd frequencies = evals.cwiseSqrt();

  return std::make_tuple(M, K, frequencies, evecs);
}

void ImprovedBarElement::PlotFrequencies(const int n)
{
  double exact_frequency = M_PI / 2;
  // std::vector<std::pair<int, double>> results;
  std::vector<int> elements;
  std::vector<double> errors;

  
  for (int i = 1; i < n; ++i)
  {
    MatrixXd M, K;
    VectorXd frequencies;
    MatrixXd evecs;
    auto start = std::chrono::high_resolution_clock::now();
    std::tie(M, K, frequencies, evecs) = Bar(i);
    auto time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - start
        ).count();

    double error = (frequencies(0) - exact_frequency) / exact_frequency * 100.0;
    printf("Num Elems: %d, Fund. Frequency: %f, Error: %f, Time: %ld\n", 
      i, frequencies[0], error, time_taken);

    elements.emplace_back(i);
    errors.emplace_back(error);
  }

  plt::plot(elements, errors, "o-");
  plt::xlim(elements.at(0), elements.at(elements.size() - 1));
  plt::xlabel("Number of Elements");
  plt::ylabel("Error (%)");
  plt::show();
}

int main()
{
  ImprovedBarElement ibe;
  ibe.PlotFrequencies(11);
  
  return 0;
}
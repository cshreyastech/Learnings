#include "TheFiniteElementMethod/03_bar_element.h"

BarElement::BarElement()
{
}

BarElement::~BarElement()
{

}

void BarElement::RemoveRow(Eigen::MatrixXd& matrix, unsigned int rowToRemove)
{
  unsigned int numRows = matrix.rows()-1;
  unsigned int numCols = matrix.cols();

  if( rowToRemove < numRows )
    matrix.block(rowToRemove,0,numRows-rowToRemove,numCols) = matrix.bottomRows(numRows-rowToRemove);

  matrix.conservativeResize(numRows,numCols);
}

void BarElement::RemoveColumn(Eigen::MatrixXd& matrix, unsigned int colToRemove)
{
  unsigned int numRows = matrix.rows();
  unsigned int numCols = matrix.cols()-1;

  if( colToRemove < numCols )
    matrix.block(0,colToRemove,numRows,numCols-colToRemove) = matrix.rightCols(numCols-colToRemove);

  matrix.conservativeResize(numRows,numCols);
}

void BarElement::ReduceDimention(const int& dof, MatrixXd& M)
{
  M.block(dof, 0, M.rows() - 1, M.cols()) = M.bottomRows(M.rows() - 1);
  M.block(0, dof, M.rows(), M.cols() - 1) = M.rightCols(M.cols() - 1);
  M.conservativeResize(M.rows() - 1, M.cols() - 1);
}

std::tuple<MatrixXd, MatrixXd, VectorXd, MatrixXd> BarElement::Bar(const int num_elems)
{
  MatrixXd m, k;
  m.resize(2, 2);
  k.resize(2, 2);
  
  m << 2, 1,
        1, 2;

  k <<  1, -1,
        -1,  1;


  // element mass and stiffness matrices for a bar 
  m /= (6.0f * static_cast<float>(num_elems));
  k *= static_cast<float>(num_elems);

  // construct global mass and stiffness matrices
  MatrixXd M = MatrixXd::Zero(num_elems + 1, num_elems + 1);
  MatrixXd K = MatrixXd::Zero(num_elems + 1, num_elems + 1);

  // Assembly of elements
  for (int i = 0; i < num_elems; ++i)
  {
    M.block(i, i, 2, 2) += m;
    K.block(i, i, 2, 2) += k;
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

void BarElement::PlotFrequencies(const int n)
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
    std::tie(M, K, frequencies, evecs) = Bar(i);

    double error = (frequencies(0) - exact_frequency) / exact_frequency * 100.0;
    // printf("Num Elems: %d, Fund. Frequency: %f, Error: %f\n", 
    //   i, frequencies[0], error);

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
  BarElement be;
  be.PlotFrequencies(11);
  
  return 0;
}
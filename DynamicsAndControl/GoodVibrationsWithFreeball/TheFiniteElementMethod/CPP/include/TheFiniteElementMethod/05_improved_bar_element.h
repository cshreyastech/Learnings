#ifndef IMPROVED_BAR_ELEMENT_H
#define IMPROVED_BAR_ELEMENT_H

#include "pch/pch.h"
#include "eigen_utils_lib/eigen_utils.h"

class ImprovedBarElement
{
public:
  ImprovedBarElement();
  ~ImprovedBarElement();

  std::tuple<MatrixXd, MatrixXd, VectorXd, MatrixXd> Bar(const int num_elems);
  void PlotFrequencies(const int n);

private:
  // https://stackoverflow.com/questions/13290395/
  // how-to-remove-a-certain-row-or-column-while-using-eigen-library-c
  void ReduceDimention(const int& dof, MatrixXd& M);
};
#endif
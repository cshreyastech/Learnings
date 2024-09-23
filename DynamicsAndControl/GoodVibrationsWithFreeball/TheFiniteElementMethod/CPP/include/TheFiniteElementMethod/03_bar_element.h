#ifndef BAR_ELEMENT_H
#define BAR_ELEMENT_H

#include "pch/pch.h"

class BarElement
{
public:
  BarElement();
  ~BarElement();

  std::tuple<MatrixXd, MatrixXd, VectorXd, MatrixXd> Bar(const int num_elems);
  void PlotFrequencies(const int n);

private:
  // https://stackoverflow.com/questions/13290395/
  // how-to-remove-a-certain-row-or-column-while-using-eigen-library-c
  void RemoveRow(Eigen::MatrixXd& matrix, unsigned int rowToRemove);
  void RemoveColumn(Eigen::MatrixXd& matrix, unsigned int colToRemove);
  void ReduceDimention(const int& dof, MatrixXd& M);
};
#endif
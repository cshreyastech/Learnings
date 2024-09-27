#ifndef EIGEN_UTILS_H
#define EIGEN_UTILS_H

#include "pch/pch.h"

class EigenUtils
{
public:
  static void RemoveRow(Eigen::MatrixXd& matrix, unsigned int rowToRemove);
  static void RemoveColumn(Eigen::MatrixXd& matrix, unsigned int colToRemove);
private:
  EigenUtils();
  ~EigenUtils();
};
#endif
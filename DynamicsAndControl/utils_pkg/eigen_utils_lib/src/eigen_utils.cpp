#include "eigen_utils_lib/eigen_utils.h"

EigenUtils::EigenUtils()
{
}

EigenUtils::~EigenUtils()
{
}

void EigenUtils::RemoveRow(Eigen::MatrixXd& matrix, unsigned int rowToRemove)
{
  unsigned int numRows = matrix.rows()-1;
  unsigned int numCols = matrix.cols();

  if( rowToRemove < numRows )
    matrix.block(rowToRemove,0,numRows-rowToRemove,numCols) = matrix.bottomRows(numRows-rowToRemove);

  matrix.conservativeResize(numRows,numCols);
}

void EigenUtils::RemoveColumn(Eigen::MatrixXd& matrix, unsigned int colToRemove)
{
  unsigned int numRows = matrix.rows();
  unsigned int numCols = matrix.cols()-1;

  if( colToRemove < numCols )
    matrix.block(0,colToRemove,numRows,numCols-colToRemove) = matrix.rightCols(numCols-colToRemove);

  matrix.conservativeResize(numRows,numCols);
}
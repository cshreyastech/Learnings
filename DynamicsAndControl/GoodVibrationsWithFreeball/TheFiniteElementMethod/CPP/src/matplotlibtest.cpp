// https://www.youtube.com/watch?v=OlbtdOAWNf8


#include "pch/pch.h"

int main()
{
  plt::plot({1, 2, 3, 4}, "*");
  plt::show();

  std::cout << "Hello world\n";

  MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  std::cout << m << std::endl;
  
  return 0;
}
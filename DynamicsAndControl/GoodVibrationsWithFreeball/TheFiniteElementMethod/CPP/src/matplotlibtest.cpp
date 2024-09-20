// https://www.youtube.com/watch?v=OlbtdOAWNf8

#include "matplotlibcpp/matplotlibcpp.h"

namespace plt = matplotlibcpp;

#include <iostream>
int main()
{
  plt::plot({1, 2, 3, 4}, "*");
  plt::show();

  std::cout << "Hello world\n";
  return 0;
}
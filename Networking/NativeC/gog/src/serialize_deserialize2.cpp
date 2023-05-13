#include <string>
#include <cstring>
#include <gog/struct_declarations.hpp>
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>


std::string convertToString(char* a, int size)
{
  int i;
  std::string s = "";
  for (i = 0; i < size; i++) {
      s = s + a[i];
  }
  return s;
}

int main()
{

  Transformation t_w_e;
  t_w_e.i = 10; t_w_e.f = -10.12345f;
  // t_w_e.t = glm::vec4(0.923984f, .0f, 1.0f, 1.0f);
  // printf("i: %d, f: %f, t[%f], t[%f], t[%f], t[%f]\n", 
  //   t_w_e.i, t_w_e.f, t_w_e.t[0], t_w_e.t[1], t_w_e.t[2], t_w_e.t[3]);

  int t_w_e_array_len = sizeof(int) + sizeof(float);
  char t_w_e_array[t_w_e_array_len];
  memcpy(t_w_e_array, &t_w_e.i, sizeof(int));
  memcpy(t_w_e_array+1, &t_w_e.f, sizeof(float));

  // for(int i = 0; i < t_w_e_array_len; i++)
  // {
  //   printf("i:%d, t_w_e_array[%d]\n", i, t_w_e_array[i]);
  // }

  int i[sizeof(int)];
  memcpy(i, t_w_e_array, sizeof(int));
  std::cout << "i: " << i << std::endl;
  return 0;
}
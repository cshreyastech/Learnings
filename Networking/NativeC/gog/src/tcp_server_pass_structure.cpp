// #include "glad/glad.h"
// #include <GLFW/glfw3.h>


#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <unistd.h>

#include <memory> // unique_ptr
#include <sys/stat.h>
#include <cmath>
#include <gog/socket_server.hpp>


#include <string>
#include <cstring>
#include <gog/struct_declarations.hpp>

int main(int argc, char** argv)
{
  const int port = 8080;

  std::unique_ptr<SocketServer> server_ptr(new SocketServer(port));
  server_ptr->ConnectToNetwork();



  server_ptr->SendEyeTrackingDims(sizeof(Transformation));


  Transformation t_w_e;
  t_w_e.i = 10; t_w_e.f = -10.12345f;
  t_w_e.t = glm::vec4(0.923984f, .0f, 1.0f, 1.0f);
  printf("i: %d, f: %f, t[%f], t[%f], t[%f], t[%f]\n", 
    t_w_e.i, t_w_e.f, t_w_e.t[0], t_w_e.t[1], t_w_e.t[2], t_w_e.t[3]);
  server_ptr->SendEyeTrackingData(t_w_e);


  // int i = -10;
  // std::cout << i << std::endl;
  // std::string serilized_int = serialize<int>(i);
  // int deserilized_int = deserialize<int>(serilized_int, false);
  // std::cout << "deserilized i: " << deserilized_int << std::endl;  
  // std::cout << "-----------------------------\n" << std::endl;
  
  // float f = -0.923749237948f;
  // std::cout << f << std::endl;
  // std::string serilized_float = serialize<float>(f);
  // int deserilized_float = deserialize<float>(serilized_float, false);
  // std::cout << "deserilized f: " << deserilized_float << std::endl;
  // std::cout << "-----------------------------\n" << std::endl;



  // std::string serilized_struct = serialize<Transformation>(t);
  // Transformation deserilized_struct = deserialize<Transformation>(serilized_struct, false);
  // std::cout << "deserilized struct: " << deserilized_struct.i << ", "
  //           << deserilized_struct.f << "," 
  //           << deserilized_struct.t[0] 
  //           << std::endl;
  // std::cout << "-----------------------------\n" << std::endl;  
  return 0;
}
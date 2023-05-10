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

int main(int argc, char** argv)
{
  const int port = 8080;

  std::unique_ptr<SocketServer> server_ptr(new SocketServer(port));
  server_ptr->ConnectToNetwork();

  server_ptr->SendEyeTrackingDims(sizeof(int));

  int counter = 9089809;
  printf("counter: %d\n", counter);
  // server_ptr->SendEyeTrackingData(counter);

  server_ptr->SendEyeTrackingData2(counter);

  // for(int counter = 0; counter < 10; counter++)
  // {
  //   server_ptr->SendEyeTrackingData(counter);
  // }

  return 0;
}
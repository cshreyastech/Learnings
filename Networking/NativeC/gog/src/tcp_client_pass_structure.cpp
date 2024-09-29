#include <memory> // unique_ptr
#include <cstdlib> // atoi

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <memory> // unique_ptr

#include "gog/socket_client.hpp"
#include "gog/struct_declarations.hpp"

int main()
{

  const std::string server_ip = "127.0.0.1";
  const int port = 8080;

  std::unique_ptr<SocketClient> client_ptr(new SocketClient(server_ip.c_str(), port));
  client_ptr->ConnectToServer();
  client_ptr->ReceiveEyeTrackingDims();

  Transformation t_w_e;
  client_ptr->ReceiveEyeTrackingData(t_w_e);
  return 0;
}
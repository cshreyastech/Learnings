#ifndef SOCKET_SERVER_HPP
#define SOCKET_SERVER_HPP

#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cctype> // isdigit
#include <sys/socket.h>
#include <netinet/in.h>
#include "server/struct_declarations.hpp"

class SocketServer {
 public:
  SocketServer(const int port);
  ~SocketServer();
  void ConnectToNetwork();
  const int ReceiveInt();  

 private:
  void DeserializeInt(int *value, unsigned char *data_arr);
  int eye_track_dims_{0};
  struct sockaddr_in server_addr_;
  struct sockaddr_in client_addr_;
  // const std::string pic_filename_{""};
  socklen_t client_len_{0};
  const size_t server_addr_size_{0};
  const int port_{0};
  int sock_fdesc_init_{0};
  int sock_fdesc_conn_{0};
};


#endif

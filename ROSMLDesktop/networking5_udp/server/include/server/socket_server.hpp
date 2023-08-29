#ifndef SOCKET_SERVER_HPP
#define SOCKET_SERVER_HPP

#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cctype> // isdigit
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h> // close
#include <sys/types.h>
#include <sys/stat.h>

#include <iostream>
#include <cassert>
#include <vector>

#include <stdio.h>
#include <strings.h>
#include <arpa/inet.h>
#include <iostream>

#include "server/struct_declarations.hpp"

class SocketServer {
 public:
  SocketServer(const int);
  ~SocketServer();
  void ConnectToNetwork();
  const int ReceiveInt();  
  void ReceiveCloud(char**, const int );

 private:
  void DeserializeInt(int*, unsigned char*);
  // void DeserializeFloat(float*, unsigned char*);

  int eye_track_dims_{0};
  struct sockaddr_in server_addr_, client_addr_;
  unsigned int server_addr_size_{0};
  unsigned int client_addr_size_{0};
  const int port_{0};
  int sock_fdesc_conn_{0};
};


#endif

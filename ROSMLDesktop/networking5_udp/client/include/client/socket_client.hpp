#ifndef SOCKET_CLIENT_HPP
#define SOCKET_CLIENT_HPP

#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cctype> // isdigit
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <sys/types.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<iostream>



#include "snappy-internal.h"
#include "snappy-sinksource.h"
#include "snappy.h"

class SocketClient {
 public:
  SocketClient(const char*, int);
  ~SocketClient();
  void ConnectToServer();
  void SendInt(const int);
  void SendCloud(char[], const int);
  
 private:
  void SerializeInt(const int*, unsigned char*);
  void SerializeFloat(const float*, unsigned char*);

  const char* hostname_;
  // int port_;
  // int pic_num_;
  // int sock_fdesc_conn_;
  const int n_eye_tracking_{0};

  struct sockaddr_in server_addr_;
  const size_t server_addr_size_{0};
  const int port_{0};
  int sock_fdesc_conn_{0};


};

#endif

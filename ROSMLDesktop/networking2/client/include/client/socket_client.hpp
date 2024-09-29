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

class SocketClient {
 public:
  SocketClient(const char*, int);
  ~SocketClient();
  void ConnectToServer();
  void SendInt(const int);
  void SendCloud(const uint8_t[], const int);
  
 private:
  void SerializeInt(const int*, unsigned char*);
  void SerializeFloat(const float*, unsigned char*);

  const char* hostname_;
  int port_;
  int pic_num_;
  int sock_fdesc_conn_;
  const int n_eye_tracking_{0};
};

#endif

#ifndef SOCKET_CLIENT_HPP
#define SOCKET_CLIENT_HPP

#include "client/struct_declarations.hpp"

class SocketClient {
 public:
  SocketClient(const char* hostname, int port);
  ~SocketClient();
  void ConnectToServer();
  void SendInt(const int value);

 private:
  void SerializeInt(const int *value, unsigned char *data_arr);

  const char* hostname_;
  int port_;
  int pic_num_;
  int sock_fdesc_conn_;
  const int n_eye_tracking_{0};
};

#endif

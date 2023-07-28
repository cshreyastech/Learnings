#ifndef SOCKET_CLIENT_HPP
#define SOCKET_CLIENT_HPP
#include <vector>

#include "client/struct_declarations.hpp"

class SocketClient {
 public:
  SocketClient(const char* hostname, int port);
  ~SocketClient();
  void ConnectToServer();
  void SendInt(const int value);
  void SendCloud(float vertices[], const int vertices_size);
  // void SendCloud(const std::vector<uint8_t> &zlibData);
  void SendCloud(const uint8_t zlibData_array[], const int array_size);

  
 private:
  void SerializeInt(const int *value, unsigned char *data_arr);
  void SerializeFloat(const float *value, unsigned char *data_arr);
  void SerializeFloatArray(float values[], const int values_size, unsigned char *data_arr);

  const char* hostname_;
  int port_;
  int pic_num_;
  int sock_fdesc_conn_;
  const int n_eye_tracking_{0};
};

#endif

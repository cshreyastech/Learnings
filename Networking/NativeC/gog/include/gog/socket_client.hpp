// https://github.com/alexanderkoumis/toy-opencv-mat-socket-server/tree/master

#ifndef SOCKET_CLIENT_HPP
#define SOCKET_CLIENT_HPP
#include <cstring>

class SocketClient {
 public:
  SocketClient(const char* hostname, int port);
  ~SocketClient();
  void ConnectToServer();

  void ReceiveEyeTrackingDims();
  void ReceiveEyeTrackingData(const int &counter);
  void ReceiveEyeTrackingData2(int &counter);


 private:
  const char* hostname_;
  int port_;
  int pic_num_;
  int socket_fdesc_;
  const int eye_track_dims_{0};

private:
  unsigned char * deserialize_int(unsigned char *buffer, int value);
  unsigned char * deserialize_temp(unsigned char *buffer, int &value);
};

#endif
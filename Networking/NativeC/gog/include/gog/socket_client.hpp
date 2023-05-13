// https://github.com/alexanderkoumis/toy-opencv-mat-socket-server/tree/master

#ifndef SOCKET_CLIENT_HPP
#define SOCKET_CLIENT_HPP

#include <string>
#include <cstring>
#include <gog/struct_declarations.hpp>

class SocketClient {
public:
  SocketClient(const char* hostname, int port);
  ~SocketClient();
  void ConnectToServer();

  void ReceiveEyeTrackingDims();

  // https://codereview.stackexchange.com/questions/260597/de-serialization-of-structs-representing-tcp-messages
  /*
   * Convert a byte string into a packet.
   */
  template <typename PacketType>
  PacketType deserialize(std::string &buf, bool partialProcessing = false);
  void ReceiveEyeTrackingData(Transformation t_w_e);

  std::string convertToString(char* a, int size);
 private:
  const char* hostname_;
  int port_;
  int pic_num_;
  int socket_fdesc_;
  const int eye_track_dims_{0};

};

#endif
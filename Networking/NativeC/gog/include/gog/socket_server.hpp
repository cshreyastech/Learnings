#ifndef SOCKET_SERVER_HPP
#define SOCKET_SERVER_HPP

#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cctype> // isdigit
#include <sys/socket.h>
#include <netinet/in.h>

class SocketServer {
 public:
  SocketServer(const int port);
  ~SocketServer();
  void ConnectToNetwork();
  void ReceiveImageDims();
  void ReceiveTextureData(unsigned char** data);

  void SendEyeTrackingDims(const int eye_track_dims);
  unsigned char * serialize_int(unsigned char *buffer, int value);
  unsigned char * serialize_temp(unsigned char *buffer, int &value);

  void SendEyeTrackingData(const int counter);
  void SendEyeTrackingData2(const int counter);

  void DestroyAllWindows();
  inline const int TextureWidth() const { return image_width_; }
  inline const int TextureHeight() const { return image_height_; }
  inline const int TextureChannels() const { return image_channels_; }


 private:
  const int image_width_{0}, image_height_{0}, image_channels_{0};

  struct sockaddr_in server_addr_;
  struct sockaddr_in client_addr_;
  const std::string pic_filename_{""};
  socklen_t client_len_{0};
  const size_t server_addr_size_{0};
  const int port_{0};
  int sock_fdesc_init_{0};
  int sock_fdesc_conn_{0};
};


#endif
// https://github.com/alexanderkoumis/toy-opencv-mat-socket-server/tree/master

#ifndef SOCKET_CLIENT_HPP
#define SOCKET_CLIENT_HPP
#include "vendor/glad/glad.h"
#include <GLFW/glfw3.h>
#include "vendor/stb_image/stb_image.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class SocketClient {
 public:
  SocketClient(const char* hostname, const int port);
  void ConnectToServer();
  void SendImageDims(const int image_width, const int image_height, const int image_channels);
  void SendImage(const unsigned char* data, const int image_width, const int image_height, const int image_channels);

 private:
  const char* hostname_;
  const int port_;
  int socket_fdesc_;
};

#endif
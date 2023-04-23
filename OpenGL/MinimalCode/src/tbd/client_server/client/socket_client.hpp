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
  SocketClient(const char* hostname, int port);
  void ConnectToServer();
  void SendImageDims(const int image_rows, const int image_cols);
  void SendImage(unsigned char* data, int image_width_, int image_height_, int image_channels_n);
  // void SendImage(unsigned char** data);
  // void SendImage(cv::Mat& image);

 private:
  const char* hostname_;
  int port_;
  int pic_num_;
  int socket_fdesc_;
};

#endif

#include "client_server/client/socket_client.hpp"

#include <memory> // unique_ptr
#include <cstdlib> // atoi

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>
#include <string>

class ImageConverter
{
public:
  ImageConverter()
  {
    this->client_ptr_ = std::unique_ptr<SocketClient>(new SocketClient(hostname_.c_str(), port_));
    client_ptr_->ConnectToServer();

    std::string image_path = "../src/res/texture/dynamic_textures/container0.jpg";
    GetImageAttributes(image_path.c_str());

    client_ptr_->SendImageDims(image_width_, image_height_, image_channels_);
    
    int i = 0;
    while(1)
    {
      image_path = "../src/res/texture/dynamic_textures/container" + std::to_string(i) + ".jpg";

      unsigned char *data; 
      GetImageData(image_path.c_str(), &data);

      client_ptr_->SendImage(data, image_width_, image_height_, image_channels_);
      free(data);

      i++;
      if(i == 10) i = 0;
    }
  }

  ~ImageConverter()
  {
    
  }

  // utility function for loading a 2D texture from file
  // ---------------------------------------------------
  void GetImageAttributes(char const* path)
  {
    unsigned char *data = stbi_load(path, &image_width_, &image_height_, &image_channels_, 0);

    if (data)
    {
      GLenum image_format_;
      if (image_channels_ == 1)
        image_format_ = GL_RED;
      else if (image_channels_ == 3)
        image_format_ = GL_RGB;
      else if (image_channels_ == 4)
        image_format_ = GL_RGBA;

      stbi_image_free(data);
    }
    else
    {
      std::cout << "Texture failed to load at path: " << path << std::endl;
      stbi_image_free(data);
    }

  }

  void GetImageData(char const * path, unsigned char** data)
  {
    int image_width, image_height, image_channels;
    *data = stbi_load(path, &image_width, &image_height, &image_channels, 0);
    if (data)
    {
      if(image_width_   != image_width   || 
         image_height   != image_height_ || 
         image_channels != image_channels)
      {
        std::cout << "Image format missmatch: " << std::endl;
        stbi_image_free(data);      
      }
    }
    else
    {
      std::cout << "Texture failed to load at path: " << path << std::endl;
      stbi_image_free(data);
    }
  }

private:
  std::unique_ptr<SocketClient> client_ptr_;
  const std::string hostname_ = "127.0.0.1";
  const int port_ = 8080;
  int image_width_{0}, image_height_{0}, image_channels_{0};
  GLenum image_format_;
};

int main(int argc, char** argv)
{
  ImageConverter ic;
  return 0;
}
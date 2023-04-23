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

    client_ptr_->SendImageDims(image_width_, image_height_);    
    
    int i = 0;
    while(1)
    {
      image_path = "../src/res/texture/dynamic_textures/container" + std::to_string(i) + ".jpg";

      unsigned char *data; 
      GetImageData(image_path.c_str(), &data);

      client_ptr_->SendImage(data, image_width_, image_height_, image_channels_n_);
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
    unsigned char *data = stbi_load(path, &image_width_, &image_height_, &image_channels_n_, 0);
    // std::cout << image_width_ << ", " << image_height_ << std::endl;

    if (data)
    {
      GLenum image_format_;
      if (image_channels_n_ == 1)
        image_format_ = GL_RED;
      else if (image_channels_n_ == 3)
        image_format_ = GL_RGB;
      else if (image_channels_n_ == 4)
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
    int width, height, image_channels_n;
    // unsigned char *data = 
    *data = stbi_load(path, &image_width_, &image_height_, &image_channels_n, 0);
    // if (data)
    // {
    //   if(image_width_ != width && image_height_ != height && image_nr_components_ != nr_components)
    //   {
    //     std::cout << "Image format missmatch: " << std::endl;
    //     stbi_image_free(data);      
    //   }
      // std::cout << data[0][2] << std::endl;
    //   // stbi_image_free(data);
    // }
    // else
    // {
    //   std::cout << "Texture failed to load at path: " << path << std::endl;
    //   stbi_image_free(data);
    // }
  }

private:
  std::unique_ptr<SocketClient> client_ptr_;
  std::string hostname_ = "127.0.0.1";
  int port_ = 8080;
  int image_width_{0}, image_height_{0}, image_channels_n_;
  GLenum image_format_;
};

int main(int argc, char** argv)
{
  ImageConverter ic;
  return 0;
}
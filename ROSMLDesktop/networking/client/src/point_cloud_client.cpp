#include <iostream>
#include <memory>

#include "client/socket_client.hpp"
#include "client/struct_declarations.hpp"
#include "client/myzlib.hpp"

int main()
{
  const std::string hostname_ = "127.0.0.1";
  const int port_ = 8080;
  std::unique_ptr<SocketClient> client_ptr;

  client_ptr = std::unique_ptr<SocketClient>(new SocketClient(hostname_.c_str(), port_));

  client_ptr->ConnectToServer();


  const int n_points = 1;
  // std::cout << "n_points: " << n_points << std::endl;
  // client_ptr->SendInt(n_points);

  // TODO: change it to actual eye tracking values
  // client_ptr->ReceiveNumberOfEyeTracking();

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  int vertices_size = n_points * 6;

  float vertices[vertices_size] = {
    -0.524111f, -0.392878f, -0.931184f, 0.635294f, 0.635294f, 0.635294f,
  };

  for(int i = 0; i < vertices_size; i++)
  {
    std::cout << i << ": " << vertices[i] << ", ";
  }
  std::cout << std::endl;


  // std::string vertices_str(reinterpret_cast<char const *>(std::begin(vertices)),
  //   reinterpret_cast<char const *>(std::end(vertices)));

  unsigned char const* p = reinterpret_cast<unsigned char const*>(vertices);
  std::string vertices_str(p, p + sizeof(vertices));

  // std::cout << "vertices_str: " << vertices_str << std::endl;

  // const float* vertices_back = reinterpret_cast<const float*>(vertices_str.c_str());
  // int len = vertices_str.size() / sizeof(float);

  // for(int i = 0; i < len; i++)
  // {
  //   std::cout << i << ": " << vertices_back[i] << ", ";
  // }
  // std::cout << std::endl;



  // for(int i = 0; i < vertices_size; i++)
  // {
  //   printf("vertices[%d]:%f\n", i, vertices[i]);
  // }

  // printf("vertices[%d]:%f\n", vertices_size - 1, vertices[vertices_size - 1]);
  // printf("vertices[%d]:%f\n", vertices_size - 23, vertices[vertices_size - 23]);
  // printf("vertices[%d]:%f\n", vertices_size - 1239, vertices[vertices_size - 1239]);

  client_ptr->SendCloud(vertices, vertices_size);
  return 0;
}
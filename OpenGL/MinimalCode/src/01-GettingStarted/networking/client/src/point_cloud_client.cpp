#include <iostream>
#include <memory>

#include "client/socket_client.hpp"
#include "client/struct_declarations.hpp"

int main()
{
  const std::string hostname_ = "127.0.0.1";
  const int port_ = 8080;
  std::unique_ptr<SocketClient> client_ptr;

  client_ptr = std::unique_ptr<SocketClient>(new SocketClient(hostname_.c_str(), port_));

  client_ptr->ConnectToServer();


  const int n_points = 10;
  // std::cout << "n_points: " << n_points << std::endl;
  // client_ptr->SendInt(n_points);

  // TODO: change it to actual eye tracking values
  // client_ptr->ReceiveNumberOfEyeTracking();

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  int vertices_size = n_points * 6;

  float vertices[vertices_size] = {
-0.524111f, -0.392878f, -0.931184f, 0.635294f, 0.635294f, 0.635294f, 
-0.522476f, -0.392882f, -0.931193f, 0.635294f, 0.635294f, 0.635294f, 
-0.520837f, -0.392883f, -0.931197f, 0.635294f, 0.635294f, 0.635294f, 
-0.519204f, -0.392889f, -0.931210f, 0.635294f, 0.635294f, 0.635294f, 
-0.517565f, -0.392890f, -0.931213f, 0.635294f, 0.635294f, 0.635294f, 
-0.515929f, -0.392893f, -0.931220f, 0.635294f, 0.635294f, 0.635294f, 
-0.514294f, -0.392897f, -0.931230f, 0.635294f, 0.635294f, 0.635294f, 
-0.512655f, -0.392899f, -0.931233f, 0.635294f, 0.635294f, 0.635294f, 
-0.511020f, -0.392903f, -0.931243f, 0.635294f, 0.635294f, 0.635294f, 
-0.509383f, -0.392906f, -0.931250f, 0.635294f, 0.635294f, 0.635294f,
  };

  for(int i = 0; i < vertices_size; i++)
  {
    printf("vertices[%d]:%f\n", i, vertices[i]);
  }

  client_ptr->SendCloud(vertices, vertices_size);
  return 0;
}
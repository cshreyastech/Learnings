// #include "glad/glad.h"
// #include <GLFW/glfw3.h>


#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <unistd.h>

#include <memory> // unique_ptr
#include <sys/stat.h>
#include <cmath>
#include <gog/socket_server.hpp>


#include <string>
#include <cstring>
#include <gog/struct_declarations.hpp>

// https://codereview.stackexchange.com/questions/260597/de-serialization-of-structs-representing-tcp-messages
/*
 * Convert a byte string into a packet.
 */
template <typename PacketType>
PacketType deserialize(std::string &buf, bool partialProcessing = false)
{
    PacketType packet;
    size_t bufSize = buf.length();
    size_t packetSize = sizeof packet;

    if (packetSize > bufSize)
        std::cerr << "Packet larger than buffer size. Partial read: " << (packetSize - bufSize) << std::endl;

    if (packetSize < bufSize && !partialProcessing)
        std::cerr << "Packet smaller than buffer size. Bytes unprocessed: " << (bufSize - packetSize) << std::endl;

    auto ptr = reinterpret_cast<char*>(&buf[0]);
    std::memcpy(&packet, ptr, (packetSize < bufSize) ? packetSize : bufSize);
    return packet;
}

/*
 * Convert a packet into a byte string.
 */
template <typename PacketType>
std::string serialize(PacketType &packet)
{
    auto ptr = reinterpret_cast<char*>(&packet);
    return std::string(ptr, ptr + sizeof packet);
}



int main(int argc, char** argv)
{
  const int port = 8080;

  // std::unique_ptr<SocketServer> server_ptr(new SocketServer(port));
  // server_ptr->ConnectToNetwork();

  // server_ptr->SendEyeTrackingDims(sizeof(int));

  // int counter = 9089809;
  // float counter = 1.234f;
  // printf("counter: %f\n", counter);
  // server_ptr->SendEyeTrackingData(counter);

  // server_ptr->SendEyeTrackingData2(counter);
  // server_ptr->SendEyeTrackingData3(counter);

  int i = -10;
  std::cout << i << std::endl;
  std::string serilized_int = serialize<int>(i);
  int deserilized_int = deserialize<int>(serilized_int, false);
  std::cout << "deserilized i: " << deserilized_int << std::endl;  
  std::cout << "-----------------------------\n" << std::endl;
  
  float f = -0.923749237948f;
  std::cout << f << std::endl;
  std::string serilized_float = serialize<float>(f);
  int deserilized_float = deserialize<float>(serilized_float, false);
  std::cout << "deserilized f: " << deserilized_float << std::endl;
  std::cout << "-----------------------------\n" << std::endl;

  Transformation t;
  t.i = 10; t.f = -10.12345f;
  t.t = glm::vec4(0.923984f, .0f, 1.0f, 1.0f);

  std::string serilized_struct = serialize<Transformation>(t);
  Transformation deserilized_struct = deserialize<Transformation>(serilized_struct, false);
  std::cout << "deserilized struct: " << deserilized_struct.i << ", "
            << deserilized_struct.f << "," 
            << deserilized_struct.t[0] 
            << std::endl;
  std::cout << "-----------------------------\n" << std::endl;  
  return 0;
}
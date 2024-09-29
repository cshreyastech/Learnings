#include <iostream>
#include <memory>
#include <vector>
#include <cassert>
#include <fstream>
#include <string>
#include <chrono>

#include "client/socket_client.hpp"
#include "client/struct_declarations.hpp"

void serialize(const char* data, float vertices[], const int vertices_length);

int main()
{
  // const std::string hostname_ = "127.0.0.1";
  const std::string hostname_ = "192.168.86.36";
  const int port_ = 8080;
  std::unique_ptr<SocketClient> client_ptr;

  client_ptr = std::unique_ptr<SocketClient>(new SocketClient(hostname_.c_str(), port_));

  client_ptr->ConnectToServer();

  std::ifstream file_handler("/home/shreyas/Downloads/cloud_data/induvidual_rows/depth_data_0.txt");
  const int n_points = 307200;
  client_ptr->SendInt(n_points);

  const int vertices_length = n_points * 6;
  const int vertices_size = vertices_length * sizeof(float);

  std::cout << "n_points: " << n_points << std::endl;
  std::cout << "vertices_length: " << vertices_length << std::endl;
  std::cout << "vertices_size: " << vertices_size << std::endl;

  float vertices[vertices_length];

  std::string each_value_str;
  int n_values_read_from_file  = 0;
  while(file_handler >> each_value_str)
  {
    std::string each_value_clean_str = 
      each_value_str.substr(0, each_value_str.find("f", 0));

    float value_float = std::stof(each_value_clean_str);

    vertices[n_values_read_from_file] = value_float;
    n_values_read_from_file++;
  }
  assert(n_points == (n_values_read_from_file)/6);
  // print_array(vertices, vertices_length);

  // https://stackoverflow.com/questions/332030/when-should-static-cast-dynamic-cast-const-cast-and-reinterpret-cast-be-used  
  // uint8_t const* p_vertices = static_cast<uint8_t const*>(vertices);
  // uint8_t const* p_vertices = (uint8_t const*)malloc(vertices_size);
  // serialize(p_vertices, vertices, vertices_length);

  const char* p_vertices = (const char*)malloc(vertices_size);
  serialize(p_vertices, vertices, vertices_length);

  char* p_vertices_compressed = 
    new char[snappy::MaxCompressedLength(vertices_size)];
  size_t p_vertices_compressed_size;

  auto compression_start = std::chrono::high_resolution_clock::now();
  snappy::RawCompress(p_vertices, vertices_size, 
    p_vertices_compressed, &p_vertices_compressed_size);
  auto compression_end = std::chrono::high_resolution_clock::now();
  long long compression_duration = 
    std::chrono::duration_cast<std::chrono::microseconds>(compression_end - compression_start).count();
  printf("Client - snappy - RawCompression(mircosec): %lld\n", compression_duration);

  client_ptr->SendInt(p_vertices_compressed_size);
  std::cout << "p_vertices_compressed_size: " << p_vertices_compressed_size << std::endl;

  for(int i = 0; i < 1; i++)
  {
    auto send_cloud_start = std::chrono::high_resolution_clock::now();
    
    client_ptr->SendCloud(p_vertices_compressed, p_vertices_compressed_size);

    auto send_cloud_end = std::chrono::high_resolution_clock::now();
    long long send_cloud_duration = 
      std::chrono::duration_cast<std::chrono::microseconds>(send_cloud_end - send_cloud_start).count();
    printf("Client - snappy - sendcloud(mircosec): %lld\n", send_cloud_duration);
  }

  delete[] p_vertices;
  delete[] p_vertices_compressed;

  // Stats
  // n_points: 307200
  // Client - snappy - RawCompression(mircosec): 56179
  // p_vertices_compressed_size: 3962497
  // Client - snappy - sendcloud(mircosec): 1328

  return 0;
}

void serialize(const char* data, float vertices[], const int vertices_length)
{
  float *q = (float*)data;
  for(int i = 0; i < vertices_length; i++)
  {
    *q = vertices[i]; q++;
  }
}
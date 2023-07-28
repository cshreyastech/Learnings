#include <iostream>
#include <memory>
#include <vector>
#include <cassert>
#include <fstream>
#include <string>

#include "client/socket_client.hpp"
#include "client/struct_declarations.hpp"
#include <decoco/decoco.hpp>


void deserialize(std::vector<uint8_t>& data, float vertices[], const int vertices_length)
{
  std::vector<uint8_t>::iterator it = data.begin();

  float *q = (float*)&(*it);

  for(int i = 0; i < vertices_length; i++)
  {
    vertices[i] = *q; q++; 
  }
}

void print_array(float vertices[], int array_size)
{
  for(int i = 0; i < array_size; i++)
  {
    std::cout << "i: " << i << ", vertices[i]: "<< vertices[i] << std::endl;
  }

  std::cout << "-------------------\n";
}

int main()
{
  const std::string hostname_ = "127.0.0.1";
  const int port_ = 8080;
  std::unique_ptr<SocketClient> client_ptr;

  client_ptr = std::unique_ptr<SocketClient>(new SocketClient(hostname_.c_str(), port_));

  client_ptr->ConnectToServer();

  std::ifstream file_handler("/home/cs20/Downloads/cloud_data_tbd/induvidual_rows/depth_data.txt");
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

  uint8_t const* p_vertices = reinterpret_cast<uint8_t const*>(vertices);
   
  std::vector<uint8_t> hello(p_vertices, p_vertices + vertices_size);


  auto compressor = Decoco::ZlibCompressor();
  std::vector<uint8_t> zlibData = compressor->compress(hello);
  auto end = compressor->flush();
  zlibData.insert(zlibData.end(), end.begin(), end.end());

  client_ptr->SendInt(zlibData.size());

  uint8_t* zlibData_array = (uint8_t*)malloc(zlibData.size());
  
  std::copy(zlibData.begin(), zlibData.end(), zlibData_array);
  client_ptr->SendCloud(zlibData_array, zlibData.size());

  delete[] zlibData_array;

  return 0;
}
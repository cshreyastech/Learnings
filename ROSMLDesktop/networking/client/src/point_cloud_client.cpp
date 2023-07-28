#include <iostream>
#include <memory>
#include <vector>
#include <cassert>
#include <fstream>
#include <string>

#include "client/socket_client.hpp"
#include "client/struct_declarations.hpp"
// #include "client/myzlib.hpp"
#include <decoco/decoco.hpp>


void deserialize(std::vector<uint8_t>& data, float vertices[], const int vertices_length)
{
  std::vector<uint8_t>::iterator it = data.begin();

  float *q = (float*)&(*it);

  // std::cout << "OOM: " << 51619 * sizeof(float) << std::endl;

  // vertices[51620] = *q; q++;
  // vertices[vertices_length - 1] = 0.0012f;
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

  std::ifstream file_handler("/home/cs20/Downloads/cloud_data_tbd/induvidual_rows/depth_data_test.txt");
  const int n_points = 2;
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
  client_ptr->SendCloud(zlibData);

  // zlibData == helloZlib;
  // auto decompressor = Decoco::ZlibDecompressor();
  // std::vector<uint8_t> plainData = decompressor->decompress(zlibData);
  // std::cout << (plainData == hello) << std::endl;


  // float vertices_check[vertices_length];

  // float* vertices_check = new float(vertices_length);

  // float* vertices_check = (float*)malloc(vertices_size);
  // deserialize(plainData, vertices_check, vertices_length); 
  // // print_array(vertices_check, vertices_length);

  // for(int i = 0; i < vertices_length; i++)
  //   assert(vertices[i] == vertices_check[i]);

  // const float compress_percent = 
  //   (((float)vertices_size - zlibData.size()) / (float)vertices_size) *100;
  // std::cout << "compress_percent:    " << compress_percent << std::endl;
  
  // std::cout << "vertices_size: " << vertices_size << std::endl;
  // std::cout << "zlibData.size(): " << zlibData.size() << std::endl;
  // std::cout << "plainData.size(): " << plainData.size() << std::endl;
  // // std::cout << "vertices_check: " << vertices_check << std::endl;


  // delete[] vertices_check;




























  // const std::string hostname_ = "127.0.0.1";
  // const int port_ = 8080;
  // std::unique_ptr<SocketClient> client_ptr;

  // client_ptr = std::unique_ptr<SocketClient>(new SocketClient(hostname_.c_str(), port_));

  // client_ptr->ConnectToServer();


  // const int n_points = 1;
  // // std::cout << "n_points: " << n_points << std::endl;
  // // client_ptr->SendInt(n_points);

  // // TODO: change it to actual eye tracking values
  // // client_ptr->ReceiveNumberOfEyeTracking();

  // // set up vertex data (and buffer(s)) and configure vertex attributes
  // // ------------------------------------------------------------------
  // int vertices_size = n_points * 6;

  // float vertices[vertices_size] = {
  //   -0.524111f, -0.392878f, -0.931184f, 0.635294f, 0.635294f, 0.635294f,
  // };

  // for(int i = 0; i < vertices_size; i++)
  // {
  //   std::cout << i << ": " << vertices[i] << ", ";
  // }
  // std::cout << std::endl;


  // // std::string vertices_str(reinterpret_cast<char const *>(std::begin(vertices)),
  // //   reinterpret_cast<char const *>(std::end(vertices)));

  // unsigned char const* p = reinterpret_cast<unsigned char const*>(vertices);
  // std::string vertices_str(p, p + sizeof(vertices));

  // // std::cout << "vertices_str: " << vertices_str << std::endl;

  // // const float* vertices_back = reinterpret_cast<const float*>(vertices_str.c_str());
  // // int len = vertices_str.size() / sizeof(float);

  // // for(int i = 0; i < len; i++)
  // // {
  // //   std::cout << i << ": " << vertices_back[i] << ", ";
  // // }
  // // std::cout << std::endl;



  // // for(int i = 0; i < vertices_size; i++)
  // // {
  // //   printf("vertices[%d]:%f\n", i, vertices[i]);
  // // }

  // // printf("vertices[%d]:%f\n", vertices_size - 1, vertices[vertices_size - 1]);
  // // printf("vertices[%d]:%f\n", vertices_size - 23, vertices[vertices_size - 23]);
  // // printf("vertices[%d]:%f\n", vertices_size - 1239, vertices[vertices_size - 1239]);

  // client_ptr->SendCloud(vertices, vertices_size);
  return 0;
}
#define MLSDK20

#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <cmath>

#include <ml_logging.h>
#include <ml_graphics.h>
#include <ml_lifecycle.h>
#include <ml_perception.h>
#include <ml_head_tracking.h>
#include <ml_input.h>

#include "app_framework/support_functions.h"
#include "app_framework/graphics_context.h"


#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <random>
#include <string>
#include <utility>
#include <vector>
#include <iostream>

#include "snappy-internal.h"
#include "snappy-sinksource.h"
#include "snappy.h"

#include <fstream>
#include <cassert>
#include <chrono>

void serialize(const char* data, float vertices[], const int vertices_length);
void deserialize(const char* data, float vertices[], const int vertices_length);

int main() {
  std::ifstream file_handler("data/res/cloud/depth_data_0.txt");
  const int n_points = 307200;

  const int vertices_length = n_points * 6;
  const int vertices_size = vertices_length * sizeof(float);

  // std::cout << "n_points: " << n_points << std::endl;
  float vertices_src[vertices_length];

  std::string each_value_str;
  int n_values_read_from_file  = 0;
  while(file_handler >> each_value_str)
  {
    std::string each_value_clean_str = 
      each_value_str.substr(0, each_value_str.find("f", 0));

    float value_float = std::stof(each_value_clean_str);

    vertices_src[n_values_read_from_file] = value_float;
    n_values_read_from_file++;
  }
  assert(n_points == (n_values_read_from_file)/6);
  file_handler.close();


  const char* p_vertices_src = (const char*)malloc(vertices_size);
  serialize(p_vertices_src, vertices_src, vertices_length);

  char* p_vertices_compressed_src = 
    new char[snappy::MaxCompressedLength(vertices_size)];
  size_t p_vertices_compressed_src_size;

  auto compression_start_time = std::chrono::high_resolution_clock::now();
  snappy::RawCompress(p_vertices_src, vertices_size, 
    p_vertices_compressed_src, &p_vertices_compressed_src_size);
  auto compression_end_time = std::chrono::high_resolution_clock::now();

  /////
  size_t p_vertices_uncompressed_dest_size = vertices_size;
  char* p_vertices_uncompressed_dest = new char[p_vertices_uncompressed_dest_size];

  auto decompression_start_time = std::chrono::high_resolution_clock::now();
  bool raw_uncompress = snappy::RawUncompress(p_vertices_compressed_src, p_vertices_compressed_src_size,
                     p_vertices_uncompressed_dest);
  auto decompression_end_time = std::chrono::high_resolution_clock::now();


  // std::cout << "raw_uncompress: " << raw_uncompress << std::endl;

  float* vertices_dest = new float[vertices_length];
  deserialize(p_vertices_uncompressed_dest, vertices_dest, vertices_length);
  
  for(int i = 0; i < vertices_length; i++)
  {
    // printf("vertices_src[%d]:%f, p_vertices_dest[%d]:%f\n", 
    // i, vertices_src[i], i, vertices_dest[i]);
    assert(vertices_src[i] == vertices_dest[i]);
  }

  // delete[] vertices_src;
  delete[] vertices_dest;

  delete[] p_vertices_src;
  delete[] p_vertices_compressed_src;
  delete[] p_vertices_uncompressed_dest;

  long long compression_duration = 
    std::chrono::duration_cast<std::chrono::microseconds>(compression_end_time - compression_start_time).count();

  long long decompression_duration = 
    std::chrono::duration_cast<std::chrono::microseconds>(decompression_end_time - decompression_start_time).count();

  float compression_ratio = 
    (((float)vertices_size - (float)p_vertices_compressed_src_size) / (float)vertices_size) * 100;


  ML_LOG_TAG(Error, APP_TAG, "Compression time - microseconds: %lld\n", compression_duration);
  ML_LOG_TAG(Error, APP_TAG, "Decompression time - microseconds: %lld\n", decompression_duration);
  ML_LOG_TAG(Error, APP_TAG, "vertices_size: %d, p_vertices_compressed_src_size: %ld\n", 
    vertices_size, p_vertices_compressed_src_size);
  ML_LOG_TAG(Error, APP_TAG, "Compession ratio: %f\n", compression_ratio);

  // Compression time - microseconds: 562832
  // Decompression time - microseconds: 137999
  // vertices_size: 7372800, p_vertices_compressed_src_size: 3962497
  // Compession ratio: 46.255196


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

void deserialize(const char* data, float vertices[], const int vertices_length)
{
  float *q = (float*)data;
  for(int i = 0; i < vertices_length; i++)
  {
    vertices[i] = *q; q++;
  }
}



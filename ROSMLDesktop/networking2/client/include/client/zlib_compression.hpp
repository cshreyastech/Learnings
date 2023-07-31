#ifndef ZLIB_COMPRESSION_HPP
#define ZLIB_COMPRESSION_HPP

#include <iostream>
#include <string.h>
#include <sstream>
#include <zlib.h>
#include <vector>

#define CHUNKSIZE 1024 * 100
class ZlibCompression
{
public:
  ZlibCompression();
  ~ZlibCompression();
  std::vector<uint8_t> Compress(uint8_t const*, const size_t);
  std::vector<uint8_t> Decompress(uint8_t const*, const size_t);

  void Deserialize(uint8_t const*, float[], const int);
  void Validate_deserialize_uint8_t_arr(uint8_t const*, float[], const int);
  void Deserialize(std::vector<uint8_t>&, float[], const int);

  // void Validate_deserialize_uint8_t_arr(uint8_t const*, 
  //   float[], const int);
};

#endif
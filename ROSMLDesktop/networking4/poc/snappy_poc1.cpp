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

int main()
{
  std::string orginal_str = "Sample String";
  std::string compressed_str;

  snappy::Compress(orginal_str.data(), orginal_str.size(), &compressed_str);

  std::cout << "Valid Compression: " << 
  snappy::IsValidCompressedBuffer(orginal_str.data(), compressed_str.size())
  << std::endl;

  std::string uncompressed_str;
  snappy::Uncompress(compressed_str.data(), 
    compressed_str.size(), &uncompressed_str);
  
  std::cout << "compare uncompressed_str: " << orginal_str.compare(uncompressed_str) << std::endl;

  char* dst = new char[orginal_str.size()];
  snappy::ByteArraySource source(orginal_str.data(), orginal_str.size());
  snappy::UncheckedByteArraySink sink(dst);
  std::cout << snappy::Uncompress(&source, &sink) << std::endl;



  return 0;
}
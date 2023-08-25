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



int main() {
  std::string orginal_str = "Sample String";
  std::string compressed_str;

  snappy::Compress(orginal_str.data(), orginal_str.size(), &compressed_str);


  ML_LOG_TAG(Error, APP_TAG, "IsValidCompressedBuffer: %d", 
    snappy::IsValidCompressedBuffer(orginal_str.data(), compressed_str.size()));

  std::string uncompressed_str;
  snappy::Uncompress(compressed_str.data(), 
    compressed_str.size(), &uncompressed_str);
  
  ML_LOG_TAG(Error, APP_TAG, "str compare: %d", orginal_str.compare(uncompressed_str));

  char* dst = new char[orginal_str.size()];
  snappy::ByteArraySource source(orginal_str.data(), orginal_str.size());
  snappy::UncheckedByteArraySink sink(dst);
  bool uncompress_valid = snappy::Uncompress(&source, &sink);

  // std::cout << snappy::Uncompress(&source, &sink) << std::endl;
  ML_LOG_TAG(Error, APP_TAG, "uncompress_valid: %d", uncompress_valid);

  ML_LOG_TAG(Error, APP_TAG, "orginal_str.data(): %s", orginal_str.data());
  ML_LOG_TAG(Error, APP_TAG, "dst: %s", dst);

	return 0;
}



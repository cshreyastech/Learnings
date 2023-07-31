#include "server/zlib_compression.hpp"

ZlibCompression::ZlibCompression()
{

}

ZlibCompression::~ZlibCompression()
{
  
}

/** Compress a STL string using zlib with given compression level and return* the binary data. */
std::vector<uint8_t> ZlibCompression::Compress(uint8_t const* in_data, 
  const size_t avail_in)
{
  int compressionlevel = Z_BEST_COMPRESSION;
  z_stream zs;                        // z_stream is zlib's control structure
  memset(&zs, 0, sizeof(zs));

  if (deflateInit(&zs, compressionlevel) != Z_OK)
    throw(std::runtime_error("deflateInit failed while compressing."));

  zs.next_in = const_cast<uint8_t*>(in_data);
  zs.avail_in = avail_in;           // set the z_stream's input

  int ret;
  uint8_t outbuffer[CHUNKSIZE];
  std::vector<uint8_t> out_data;

  // retrieve the compressed bytes blockwise
  do {
    zs.next_out = reinterpret_cast<uint8_t*>(outbuffer);
    zs.avail_out = sizeof(outbuffer);

    ret = deflate(&zs, Z_FINISH);

    if(out_data.size() < zs.total_out)
    {
      // append the block to the output
      std::vector<uint8_t> out_data_temp;
      out_data_temp.assign(std::begin(outbuffer), std::end(outbuffer));
      out_data.insert(std::end(out_data), 
        std::begin(out_data_temp), std::end(out_data_temp));
    }
  } while (ret == Z_OK);

  deflateEnd(&zs);
  if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
    std::ostringstream oss;
    oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
    throw(std::runtime_error(oss.str()));
  }

  return out_data;
}

/** Decompress an STL string using zlib and return the original data. */
std::vector<uint8_t> ZlibCompression::Decompress(uint8_t const* in_data, const size_t avail_in) {
  z_stream zs;                        // z_stream is zlib's control structure
  memset(&zs, 0, sizeof(zs));

  if (inflateInit(&zs) != Z_OK)
    throw(std::runtime_error("inflateInit failed while decompressing."));

  zs.next_in = const_cast<uint8_t*>(in_data);
  zs.avail_in = avail_in;

  int ret;
  uint8_t outbuffer[CHUNKSIZE];
  std::vector<uint8_t> out_data;

  // get the decompressed bytes blockwise using repeated calls to inflate
  do {
    zs.next_out = reinterpret_cast<uint8_t*>(outbuffer);
    zs.avail_out = sizeof(outbuffer);

    ret = inflate(&zs, 0);

    if(out_data.size() < zs.total_out)
    {
      // append the block to the output
      std::vector<uint8_t> out_data_temp;
      out_data_temp.assign(std::begin(outbuffer), std::end(outbuffer));
      out_data.insert(std::end(out_data), 
      std::begin(out_data_temp), std::end(out_data_temp));
    }
  } while (ret == Z_OK);
    
  inflateEnd(&zs);
  if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
    std::ostringstream oss;
    oss << "Exception during zlib decompression: (" << ret << ") "
        << zs.msg;
    throw(std::runtime_error(oss.str()));
  }

  return out_data;
}

void ZlibCompression::Deserialize(uint8_t const* data, 
  float vertices[], const int vertices_length)
{
  float *q = (float*)data;
  for(int i = 0; i < vertices_length; i++)
  {
    vertices[i] = *q; q++;
  }
}

// void ZlibCompression::Validate_deserialize_uint8_t_arr(uint8_t const* data, 
//   float vertices_client[], const int vertices_length)
// {
//   float vertices_check[vertices_length];
//   deserialize(data, vertices_check, vertices_length);
//   for(int i = 0; i < vertices_length; i++)
//   {
//     assert(vertices_client[i] == vertices_check[i]);
//   }
// }

void ZlibCompression::Deserialize(std::vector<uint8_t>& data, 
  float vertices[], const int vertices_length)
{
  std::vector<uint8_t>::iterator it = data.begin();

  float *q = (float*)&(*it);

  for(int i = 0; i < vertices_length; i++)
  {
    vertices[i] = *q; q++; 
  }
}
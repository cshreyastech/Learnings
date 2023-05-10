#include <memory> // unique_ptr
#include <cstdio>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h> // close
#include <sys/stat.h>


#include "gog/socket_client.hpp"

SocketClient::SocketClient(const char* hostname, int port) :
    hostname_ (hostname),
    port_(port),
    pic_num_(0),
    socket_fdesc_(0) {}

void SocketClient::ConnectToServer() {
  struct addrinfo addrinfo_hints;
  struct addrinfo* addrinfo_resp;

  // Specify criteria for address structs to be returned by getAddrinfo
  memset(&addrinfo_hints, 0, sizeof(addrinfo_hints));
  addrinfo_hints.ai_socktype = SOCK_STREAM;
  addrinfo_hints.ai_family = AF_INET;

  // Populate addr_info_resp with address responses matching hints
  if (getaddrinfo(hostname_, std::to_string(port_).c_str(),
                  &addrinfo_hints, &addrinfo_resp) != 0) {
    perror("Couldn't connect to host!");
    exit(1);
  }

  // Create socket file descriptor for server
  socket_fdesc_ = socket(addrinfo_resp->ai_family, addrinfo_resp->ai_socktype,
                        addrinfo_resp->ai_protocol);
  if (socket_fdesc_ == -1) {
    perror("Error opening socket");
    exit(1);
  }

  // Connect to server specified in address struct, assign process to server
  // file descriptor
  if (connect(socket_fdesc_, addrinfo_resp->ai_addr,
              addrinfo_resp->ai_addrlen) == -1) {
    perror("Error connecting to address");
    exit(1);
  }

  free(addrinfo_resp);
}

void SocketClient::ReceiveEyeTrackingDims()
{
  ssize_t bytes_sent = 0;
  size_t dims_size = 0;

  size_t sizeof_dims = sizeof(eye_track_dims_);

  if (bytes_sent = recv(socket_fdesc_, (char*)&eye_track_dims_, sizeof_dims, 0) == -1) {
    printf("ERROR!: recv failed\n"
           "sock_fdesc: %d\n"
           "image_size: %zu\n"
           "bytes_sent: %zu\n", socket_fdesc_, dims_size, bytes_sent);
    exit(1);
  }
  else {
      printf("Eye tracking dimensions: [%d]\n", eye_track_dims_);
    }
}

void SocketClient::ReceiveEyeTrackingData(const int &counter)
{
  ssize_t bytes_received = 0;
  size_t dims_size = 0;

  size_t sizeof_dims = sizeof(int);

  if (bytes_received = recv(socket_fdesc_, (char*)&counter, sizeof_dims, 0) == -1) {
    printf("ERROR!: recv failed\n"
           "sock_fdesc: %d\n"
           "image_size: %zu\n"
           "bytes_received: %zu\n", socket_fdesc_, dims_size, bytes_received);
    exit(1);
  }
  else {
      // printf("Eye tracking: [%d]\n", counter);
      printf("Received %ld bytes of %ld byte int at port %d, data:[%d]\n",
         bytes_received, sizeof_dims, port_, counter);
    }
}

unsigned char * SocketClient::deserialize_int(unsigned char *buffer, int value)
{
  /* Write big-endian int value into buffer; assumes 32-bit int and 8-bit char. */
  // buffer[0] = value >> 24;
  // buffer[1] = value >> 16;
  // buffer[2] = value >> 8;
  // buffer[3] = value;

  // value = (buffer[0] << 24) + (buffer[1] << 16) + (buffer[2] << 8) + (buffer[3] << 0);

  value = 0;
  value |= ((long)buffer[0]) << 24;
  value |= ((long)buffer[1]) << 16;
  value |= ((long)buffer[2]) << 8;
  value |= ((long)buffer[3]);

  printf("value: %d\n", value);
  return buffer + 4;
}

unsigned char * SocketClient::deserialize_temp(unsigned char *buffer, int &value)
{
  buffer = deserialize_int(buffer, value);
  return buffer;
}

void SocketClient::ReceiveEyeTrackingData2(int &counter)
{
  int num_bytes = 0;
  int total_num_bytes = 0;
  size_t sizeof_dims = sizeof(int);


  unsigned char sock_data[sizeof_dims];

  // Save image data to buffer
  for (int i = 0; i < sizeof_dims; i += num_bytes) {
    num_bytes = recv(socket_fdesc_, sock_data + i, sizeof_dims - i, 0);
    total_num_bytes += num_bytes;

    if (num_bytes == -1) {
      printf("ERROR!: recv failed\n"
             "i: %d\n"
             "sock_fdesc: %d\n"
             "data_size: %ld\n"
             "num_bytes: %d\n", i, socket_fdesc_, sizeof_dims, num_bytes);
      exit(1);
    }
  }

  // printf("sock_data %d, %d, %d, %d\n", sock_data[0], sock_data[1], sock_data[2], sock_data[3]);

  deserialize_temp(sock_data, counter);


}



// void SocketServer::ReceiveTextureData(unsigned char** data)
// {

//   int num_bytes = 0;
//   int total_num_bytes = 0;
//   int image_size = image_width_ * image_height_ * image_channels_;

//   // int image_size = 512 * 512 * 3;

//   // Allocate space for image buffer
//   unsigned char sock_data[image_size];

//   // Save image data to buffer
//   for (int i = 0; i < image_size; i += num_bytes) {
//     num_bytes = recv(sock_fdesc_conn_, sock_data + i, image_size - i, 0);
//     total_num_bytes += num_bytes;

//     if (num_bytes == -1) {
//       printf("ERROR!: recv failed\n"
//              "i: %d\n"
//              "sock_fdesc: %d\n"
//              "image_size: %d\n"
//              "num_bytes: %d\n", i, sock_fdesc_conn_, image_size, num_bytes);
//       exit(1);
//     }
//   }

//   // printf("image_size: %d, total_num_bytes: %d\n", image_size, total_num_bytes);

//   *data = sock_data;
// }


SocketClient::~SocketClient()
{
  close(socket_fdesc_);
  printf("Closed connection to %s at port %d\n", hostname_, port_);
}
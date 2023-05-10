#include <unistd.h> // close
#include <sys/types.h>
#include <sys/stat.h>

#include <iostream>
#include <cassert>

#include "gog/socket_server.hpp"

SocketServer::SocketServer(const int port) :
    client_len_(0),
    server_addr_size_(sizeof(server_addr_)),
    port_(port),
    sock_fdesc_init_(0),
    sock_fdesc_conn_(0) {
  client_len_ = server_addr_size_;
}

void SocketServer::ConnectToNetwork() {

  // Initialize Socket
  sock_fdesc_init_ = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fdesc_init_ == -1) {
    close(sock_fdesc_init_);
    perror("Couldn't create socket!\n");
    exit(1);
  }

  // Zero out server address struct
  memset((char*)&server_addr_, 0, server_addr_size_);

  // Set server address struct
  server_addr_.sin_family = AF_INET;
  server_addr_.sin_addr.s_addr = INADDR_ANY;
  server_addr_.sin_port = htons(port_);

  // Assign server address to initial socket file descriptor
  if (bind(sock_fdesc_init_, (struct sockaddr*)&server_addr_,
           server_addr_size_) == -1) {
    perror("Couldn't bind initial socket file descriptor!");
    printf("Trying again after killing existing process on port %d...\n",
           port_);
    close(sock_fdesc_init_);
    if (bind(sock_fdesc_init_, (struct sockaddr*)&server_addr_,
             server_addr_size_) == -1) {
      perror("Couldn't bind initial socket file descriptor after retry!");
      exit(1);
    }
    printf("Successful bind to port %d after killing previous process\n",
           port_);
  }

  // Enable listening on initial socket file descriptor
  listen(sock_fdesc_init_, 5);

  // Block process until connection with client has been established.
  // 'client_fdesc' set as new file descriptor to be used for communication
  sock_fdesc_conn_ = accept(sock_fdesc_init_, (struct sockaddr*)&client_addr_,
                            &client_len_);
  if (sock_fdesc_conn_ == -1) {
    perror("ERROR! Client couldn't connect!");
    exit(1);
  }
}

void SocketServer::ReceiveImageDims() {

  ssize_t bytes_sent = 0;
  size_t dims_size = 0;

  size_t sizeof_dims = sizeof(image_height_);

  if (bytes_sent = recv(sock_fdesc_conn_, (char*)&image_width_, sizeof_dims, 0) == -1) {
    printf("ERROR!: recv failed\n"
           "sock_fdesc: %d\n"
           "image_size: %zu\n"
           "bytes_sent: %zu\n", sock_fdesc_conn_, dims_size, bytes_sent);
    exit(1);
  }
  else {
      printf("Image dimensions: [%d]\n", image_width_);
    }

  if (bytes_sent = recv(sock_fdesc_conn_, (char*)&image_height_, sizeof_dims, 0) == -1) {
    printf("ERROR!: recv failed\n"
           "sock_fdesc: %d\n"
           "image_size: %zu\n"
           "bytes_sent: %zu\n", sock_fdesc_conn_, dims_size, bytes_sent);
    exit(1);
  }
  printf("Image dimensions: [%dx%d]\n", image_width_, image_height_);

  if (bytes_sent = recv(sock_fdesc_conn_, (char*)&image_channels_, sizeof_dims, 0) == -1) {
    printf("ERROR!: recv failed\n"
           "sock_fdesc: %d\n"
           "image_size: %zu\n"
           "bytes_sent: %zu\n", sock_fdesc_conn_, dims_size, bytes_sent);
    exit(1);
  }
  printf("Image dimensions: [%dx%dx%d]\n", image_width_, image_height_, image_channels_);
}

void SocketServer::ReceiveTextureData(unsigned char** data)
{

  int num_bytes = 0;
  int total_num_bytes = 0;
  int image_size = image_width_ * image_height_ * image_channels_;

  // int image_size = 512 * 512 * 3;

  // Allocate space for image buffer
  unsigned char sock_data[image_size];

  // Save image data to buffer
  for (int i = 0; i < image_size; i += num_bytes) {
    num_bytes = recv(sock_fdesc_conn_, sock_data + i, image_size - i, 0);
    total_num_bytes += num_bytes;

    if (num_bytes == -1) {
      printf("ERROR!: recv failed\n"
             "i: %d\n"
             "sock_fdesc: %d\n"
             "image_size: %d\n"
             "num_bytes: %d\n", i, sock_fdesc_conn_, image_size, num_bytes);
      exit(1);
    }
  }

  // printf("image_size: %d, total_num_bytes: %d\n", image_size, total_num_bytes);

  *data = sock_data;
}

void SocketServer::SendEyeTrackingDims(const int eye_track_dims)
{
  // Send number of width to server
  if (send(sock_fdesc_conn_, (char*)&eye_track_dims, sizeof(eye_track_dims), 0) == -1) {
    perror("Error sending eye_track_dims");
    exit(1);
  }
}

void SocketServer::SendEyeTrackingData(int counter)
{
  ssize_t bytes_received = 0;
  size_t dims_size = 0;

  size_t sizeof_dims = sizeof(int);

  // int size = 1;
  bytes_received = send(sock_fdesc_conn_, (char*)&counter, sizeof_dims, 0);
  printf("Sent %ld bytes of %ld byte int to port %d\n",
         bytes_received, sizeof_dims, port_);
}



unsigned char * SocketServer::serialize_int(unsigned char *buffer, int value)
{
  /* Write big-endian int value into buffer; assumes 32-bit int and 8-bit char. */
  buffer[0] = value >> 24;
  buffer[1] = value >> 16;
  buffer[2] = value >> 8;
  buffer[3] = value;

  return buffer + 4;
}

unsigned char * SocketServer::serialize_temp(unsigned char *buffer, int &value)
{
  buffer = serialize_int(buffer, value);
  return buffer;
}

void SocketServer::SendEyeTrackingData2(int counter)
{
  ssize_t bytes_received = 0;
  size_t dims_size = 0;

  size_t sizeof_dims = sizeof(int);
  printf("sizeof_dims %ld\n", sizeof_dims);

  unsigned char buffer[sizeof_dims], *ptr;
  ptr = serialize_temp(buffer, counter);

  printf("buffer %d, %d, %d, %d\n", buffer[0], buffer[1], buffer[2], buffer[3]);


  send(sock_fdesc_conn_, buffer, sizeof_dims, 0);
}



void SocketServer::SendEyeTrackingData3(const float counter)
{
  // ssize_t bytes_received = 0;
  // size_t dims_size = 0;



  // size_t sizeof_dims = sizeof(int);
  // printf("sizeof_dims %ld\n", sizeof_dims);

  // unsigned char buffer[sizeof_dims], *ptr;
  // ptr = serialize_temp(buffer, counter);

  // printf("buffer %d, %d, %d, %d\n", buffer[0], buffer[1], buffer[2], buffer[3]);


  // send(sock_fdesc_conn_, buffer, sizeof_dims, 0);
}


SocketServer::~SocketServer()
{
  // closing the listening socket
  shutdown(sock_fdesc_conn_, SHUT_RD);
  // closing the connected socket
  close(sock_fdesc_init_);
  printf("Closed socket at port %d\n", port_); 

  // TBD
  // https://stackoverflow.com/questions/12730477/close-is-not-closing-socket-properly 
}
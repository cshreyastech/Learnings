#include <unistd.h> // close
#include <sys/types.h>
#include <sys/stat.h>

#include <iostream>
#include <cassert>
#include <algorithm>

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
  eye_track_dims_ = eye_track_dims;

  // Send number of width to server
  if (send(sock_fdesc_conn_, (char*)&eye_track_dims, sizeof(eye_track_dims), 0) == -1) {
    perror("Error sending eye_track_dims");
    exit(1);
  }
}


/*
 * Convert a packet into a byte string.
 */
template <typename PacketType>
std::string SocketServer::serialize(PacketType &packet)
{
  auto ptr = reinterpret_cast<char*>(&packet);
  return std::string(ptr, ptr + sizeof packet);
}

void SocketServer::SendEyeTrackingData(Transformation t_w_e)
{
  ssize_t bytes_sent = 0;
  size_t dims_size = 0;

  size_t sizeof_dims = eye_track_dims_;
  std::string serilized_t_w_e_str = serialize<Transformation>(t_w_e);
  // std::string serilized_t_w_e_str = "012345678901234567890123";
  // printf("serilized_t_w_e_str: %s\n", serilized_t_w_e_str.c_str());
  sizeof_dims = serilized_t_w_e_str.length() + 1;
  //1----------------------------------//
  // char serilized_t_w_e_array[serilized_t_w_e_str.length()];
  // strcpy(serilized_t_w_e_array, serilized_t_w_e_str.c_str());

  // unsigned char serilized_t_w_e_unsigned_array[sizeof(serilized_t_w_e_array)];
  // std::copy(serilized_t_w_e_array, 
  //   serilized_t_w_e_array + sizeof(serilized_t_w_e_array),
  //   serilized_t_w_e_unsigned_array);

  unsigned char serilized_t_w_e_unsigned_array[sizeof_dims];
  strcpy(reinterpret_cast<char*>(serilized_t_w_e_unsigned_array), serilized_t_w_e_str.c_str());

  for(int i = 0; i < sizeof_dims; i++)
  {
    printf("serilized_t_w_e_unsigned_array[%d]=%c\n", i, serilized_t_w_e_unsigned_array[i]);
  }

  bytes_sent = send(sock_fdesc_conn_, serilized_t_w_e_unsigned_array, sizeof_dims, 0);
  printf("Sent %ld bytes of %ld byte int to port %d\n",
         bytes_sent, sizeof_dims, port_);  
  


  //2----------------------------------//

  // unsigned char serilized_t_w_e_unsigned_array[serilized_t_w_e_str.length() + 1];
  // std::strncpy(serilized_t_w_e_unsigned_array, 
  //   serilized_t_w_e_str,
  //   sizeof(serilized_t_w_e_unsigned_array));

  // sizeof_dims = sizeof(serilized_t_w_e_unsigned_array);
  // bytes_sent = send(sock_fdesc_conn_, serilized_t_w_e_unsigned_array, sizeof_dims, 0);
  // printf("Sent %ld bytes of %ld byte int to port %d\n",
  //        bytes_sent, sizeof_dims, port_);  
  //----------------------------------//




  // unsigned char serilized_t_w_e_array[sizeof_dims];
  // strcpy(static_cast<char*>(serilized_t_w_e_array), serilized_t_w_e_str.c_str());

  // // for(int i = 0; i < sizeof_dims; i++)
  // // {
  // //   printf("sock_data[%d]=%c\n", i, serilized_t_w_e_array[i]);
  // // }
  // // printf("serilized_t_w_e: %s\n", serilized_t_w_e.c_str());
  // bytes_sent = send(sock_fdesc_conn_, serilized_t_w_e_array, sizeof_dims, 0);
  // printf("Sent %ld bytes of %ld byte int to port %d\n",
  //        bytes_sent, sizeof_dims, port_);

  // unsigned char data_arr[sizeof_dims];
  // int num_bytes = send(sock_fdesc_conn_, data_arr, sizeof_dims, 0);

  // // printf("Sent %d bytes of %d-byte image to port %d\n",
  // //        num_bytes, image_size, port_);

  // int image_size = eye_track_dims_;
  // unsigned char data_arr[image_size];

  // std::string serilized_t_w_e = serialize<Transformation>(t_w_e);
  // unsigned char
  // memcpy(data_arr, serilized_t_w_e.data, image_size);
  // int num_bytes = send(socket_fdesc_, data_arr, image_size, 0);

  // printf("Sent %d bytes of %d-byte image to port %d\n",
  //        num_bytes, image_size, port_);


}

SocketServer::~SocketServer()
{
  // closing the listening socket
  shutdown(sock_fdesc_conn_, SHUT_RDWR);
  // closing the connected socket
  close(sock_fdesc_init_);
  printf("Closed socket at port %d\n", port_); 

  // TBD
  // https://stackoverflow.com/questions/12730477/close-is-not-closing-socket-properly 
}
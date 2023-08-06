#include "server/socket_server.hpp"

#include <unistd.h> // close
#include <sys/types.h>
#include <sys/stat.h>

#include <iostream>
#include <cassert>

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

void SocketServer::DeserializeInt(int *value, unsigned char *data_arr)
{
  int *q = (int*)data_arr;
  *value = *q; q++;
}

void SocketServer::DeserializeFloat(float *value, unsigned char *data_arr)
{
  float *q = (float*)data_arr;
  *value = *q; q++;
}

const int SocketServer::ReceiveInt()
{
  int num_bytes = 0;
  int total_num_bytes = 0;
  int packet_size = sizeof(const int);

  // Allocate space for image buffer
  unsigned char data_arr[packet_size];

  num_bytes = recv(sock_fdesc_conn_, data_arr, packet_size, 0);

  printf("Received packet_size: %d\n", packet_size);
  int value;
  DeserializeInt(&value, data_arr);
  return value;
}

void SocketServer::ReceiveCloud(std::vector<uint8_t>& zlibData, const int zlibData_size)
{
  int num_bytes = 0;
  int total_num_bytes = 0;
  int packet_size = zlibData_size;

  // Allocate space for image buffer
  uint8_t data_arr[packet_size];

  // Save image data to buffer
  for (int i = 0; i < packet_size; i += num_bytes) {
    num_bytes = recv(sock_fdesc_conn_, data_arr + i, packet_size - i, 0);
    total_num_bytes += num_bytes;

    if (num_bytes == -1) {
      printf("ERROR!: recv failed\n"
             "i: %d\n"
             "sock_fdesc: %d\n"
             "packet_size: %d\n"
             "num_bytes: %d\n", i, sock_fdesc_conn_, packet_size, num_bytes);
      exit(1);
    }
  }

  printf("Received packet_size: %d\n", packet_size);

  for(int i = 0; i < packet_size; i++)
  {
    zlibData.emplace_back(data_arr[i]);    
  }
}

SocketServer::~SocketServer()
{
  close(sock_fdesc_conn_);
  printf("Closed socket at port %d\n", port_);    
}
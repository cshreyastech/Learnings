#include "client/socket_client.hpp"

#include <memory> // unique_ptr
#include <cstdio>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h> // close
#include <cstring>

SocketClient::SocketClient(const char* hostname, int port) :
  server_addr_size_(sizeof(server_addr_)),
  hostname_ (hostname),
  port_(port),
  sock_fdesc_conn_(0) {}

void SocketClient::ConnectToServer() {

  sock_fdesc_conn_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock_fdesc_conn_ == -1) {
    close(sock_fdesc_conn_);
    perror("Couldn't create socket!\n");
    exit(1);
  }

  // Zero out server address struct
  memset((char*)&server_addr_, 0, server_addr_size_);


  // Set server address struct
  server_addr_.sin_family = AF_INET;
  server_addr_.sin_addr.s_addr = inet_addr(hostname_);
  server_addr_.sin_port = htons(port_);
  
  // Connect to server specified in address struct, assign process to server
  // file descriptor
  if (connect(sock_fdesc_conn_, (struct sockaddr *)&server_addr_,
              server_addr_size_) == -1) {
    perror("Error connecting to address");
    exit(1);
  }
}

void SocketClient::SerializeInt(const int *value, unsigned char *data_arr)
{
  int *q = (int*)data_arr;

  *q = *value; q++;
}

void SocketClient::SerializeFloat(const float *value, unsigned char *data_arr)
{
  float *q = (float*)data_arr;

  *q = *value; q++;
}

void SocketClient::SendInt(const int value)
{
  const int packet_size = sizeof(value);
  unsigned char data_arr[packet_size];

  SerializeInt(&value, data_arr);

  // int data_size = send(sock_fdesc_conn_, data_arr, packet_size, 0);
  int data_size = sendto(sock_fdesc_conn_, data_arr, packet_size, 0, 
    (struct sockaddr*)NULL, server_addr_size_);

  printf("Sent data_size: %d\n", data_size);
}

void SocketClient::SendCloud(char data[], const int data_size)
{
  // int sent_data_size = send(sock_fdesc_conn_, data, data_size, 0);
  unsigned int batch_size = 1024 * 1;
  int num_bytes = 0;
  int total_num_bytes = 0;
  int packet_size = data_size;


  // num_bytes = (data_size - total_num_bytes) < batch_size ? data_size : batch_size;
  while(total_num_bytes < data_size) {
        num_bytes = 
    (data_size - total_num_bytes) < batch_size ? (data_size - total_num_bytes) : batch_size;

    num_bytes = sendto(sock_fdesc_conn_, data + total_num_bytes, num_bytes, 0, 
      (struct sockaddr*)NULL, server_addr_size_);

    if (num_bytes == -1) {
      printf("ERROR!: recv failed\n"
             "sock_fdesc: %d\n"
             "data_size: %d\n"
             "num_bytes: %d\n", sock_fdesc_conn_, data_size, num_bytes);
      exit(1);
    }

    total_num_bytes += num_bytes;

    printf("data_size: %d, num_bytes: %d, total_num_bytes: %d\n", 
      data_size, num_bytes, total_num_bytes);

    // usleep(1000000);

  }





  // int sent_data_size = sendto(sock_fdesc_conn_, data, data_size, 0, 
  //   (struct sockaddr*)NULL, server_addr_size_);

  // printf("data: %d data_size: %d\n", data_size, data_arr_size); 
}

SocketClient::~SocketClient()
{
  close(sock_fdesc_conn_);
  printf("Closed connection to %s at port %d\n", hostname_, port_);
}
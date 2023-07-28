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
    hostname_ (hostname),
    port_(port),
    pic_num_(0),
    sock_fdesc_conn_(0) {}

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
  sock_fdesc_conn_ = socket(addrinfo_resp->ai_family, addrinfo_resp->ai_socktype,
                        addrinfo_resp->ai_protocol);
  if (sock_fdesc_conn_ == -1) {
    perror("Error opening socket");
    exit(1);
  }

  // Connect to server specified in address struct, assign process to server
  // file descriptor
  if (connect(sock_fdesc_conn_, addrinfo_resp->ai_addr,
              addrinfo_resp->ai_addrlen) == -1) {
    perror("Error connecting to address");
    exit(1);
  }

  free(addrinfo_resp);
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

void SocketClient::SerializeFloatArray(float values[], const int values_size, unsigned char *data_arr)
{

  float *q = (float*)data_arr;

  // float* value = &values[0];
  // *q = *value; q++;

  // value = &values[1];
  // *q = *value; q++;

  for(int i = 0; i < values_size; i++)
  {
    float* value = &values[i];
    *q = *value; q++;
  }
}

void SocketClient::SendInt(const int value)
{
  const int packet_size = sizeof(value);
  unsigned char data_arr[packet_size];

  SerializeInt(&value, data_arr);

  int data_size = send(sock_fdesc_conn_, data_arr, packet_size, 0);

  printf("Sent data_size: %d\n", data_size);
}


void SocketClient::SendCloud(float values[], const int vertices_size)
{
  const int packet_size = sizeof(float) * vertices_size;

  unsigned char data_arr[packet_size];
  // printf("vertices_size: %d, packet_size: %d\n", vertices_size, packet_size);

  // const float value = -0.524111f;
  // printf("value: %f\n", value);

  // SerializeFloat(&value, data_arr);



  // SerializeFloatArray(values, data_arr);
  // SerializeFloatArray(values, vertices_size, data_arr);

  int data_size = send(sock_fdesc_conn_, data_arr, packet_size, 0);
  printf("Sent data_size: %d\n", data_size);
}

void SocketClient::SendCloud(const std::vector<uint8_t> &zlibData)
{
  printf("zlibData.size() -SocketClient: %ld\n", zlibData.size());

  uint8_t zlibData_unsigned_char[zlibData.size()];
  std::copy(zlibData.begin(), zlibData.end(), zlibData_unsigned_char);

  int data_size = send(sock_fdesc_conn_, zlibData_unsigned_char, zlibData.size(), 0);
  printf("Sent data_size: %d\n", data_size); 
}

SocketClient::~SocketClient()
{
  close(sock_fdesc_conn_);
  printf("Closed connection to %s at port %d\n", hostname_, port_);
}
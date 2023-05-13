#include <memory> // unique_ptr
#include <cstdio>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h> // close
#include <sys/stat.h>

#include "gog/socket_client.hpp"
#include <bits/stdc++.h>

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


template <typename PacketType>
PacketType SocketClient::deserialize(std::string &buf, bool partialProcessing)
{
  PacketType packet;
  size_t bufSize = buf.length();
  size_t packetSize = sizeof packet;

  if (packetSize > bufSize)
    printf("Packet larger than buffer size. Partial read: %ld\n", (packetSize - bufSize));

  if (packetSize < bufSize && !partialProcessing)
    printf("Packet smaller than buffer size. Bytes unprocessed: %ld\n", (bufSize - packetSize));

  auto ptr = reinterpret_cast<char*>(&buf[0]);
  std::memcpy(&packet, ptr, (packetSize < bufSize) ? packetSize : bufSize);
  return packet;
}


std::string SocketClient::convertToString(char* a, int size)
{
  int i;
  std::string s = "";
  for (i = 0; i < size; i++) {
      s = s + a[i];
  }
  return s;
}

void SocketClient::ReceiveEyeTrackingData(Transformation t_w_e)
{
  int num_bytes = 0;
  int total_num_bytes = 0;
  int image_size = eye_track_dims_ + 1;

  // int image_size = 512 * 512 * 3;

  // Allocate space for image buffer
  unsigned char serilized_t_w_e_unsigned_array[image_size];

  // Save image data to buffer
  for (int i = 0; i < image_size; i += num_bytes) {
    num_bytes = recv(socket_fdesc_, serilized_t_w_e_unsigned_array + i, image_size - i, 0);
    total_num_bytes += num_bytes;

    if (num_bytes == -1) {
      printf("ERROR!: recv failed\n"
             "i: %d\n"
             "sock_fdesc: %d\n"
             "image_size: %d\n"
             "num_bytes: %d\n", i, socket_fdesc_, image_size, num_bytes);
      exit(1);
    }
  }
  printf("image_size: %d, total_num_bytes: %d\n", image_size, total_num_bytes);
  for(int i = 0; i < total_num_bytes; i++)
  {
    printf("serilized_t_w_e_unsigned_array[%d]=%c\n", i, serilized_t_w_e_unsigned_array[i]);
  }

  std::string serilized_t_w_e_str = (const char*)serilized_t_w_e_unsigned_array;
  printf("serilized_string length: %ld\n", serilized_t_w_e_str.length());
  // std::string output = deserialize<std::string>(serilized_t_w_e_str, false);
  // printf("output: %s\n", output.c_str());


  // t_w_e = 
  // printf("i: %d, f: %f, t[%f], t[%f], t[%f], t[%f]\n", 
  //   t_w_e.i, t_w_e.f, t_w_e.t[0], t_w_e.t[1], t_w_e.t[2], t_w_e.t[3]);

  // for(int i = 0; i < total_num_bytes; i++)
  // {
  //   printf("sock_data[%d]=%c\n", i, sock_data[i]);
  // }
  // sock_data[image_size] = '\0';
  // printf("sock_data[%c]\n", sock_data[6]);
  // std::string serilized_t_w_e = convertToString(sock_data, image_size);
  // printf("serilized_string length: %ld\n", serilized_t_w_e.length());
  // printf("serilized_t_w_e: %s\n", serilized_t_w_e.c_str());
  
  
  // t_w_e = deserialize<Transformation>(serilized_t_w_e, false);
  // printf("i: %d, f: %f, t[%f], t[%f], t[%f], t[%f]\n", 
  //   t_w_e.i, t_w_e.f, t_w_e.t[0], t_w_e.t[1], t_w_e.t[2], t_w_e.t[3]);


  // *data = sock_data;
}

SocketClient::~SocketClient()
{
  close(socket_fdesc_);
  printf("Closed connection to %s at port %d\n", hostname_, port_);
}
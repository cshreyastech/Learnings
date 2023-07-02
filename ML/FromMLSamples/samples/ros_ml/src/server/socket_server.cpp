#include "server/socket_server.hpp"

#include <unistd.h> // close
#include <sys/types.h>
#include <sys/stat.h>

SocketServer::SocketServer(const int port) :
    client_len_(0),
    server_addr_size_(sizeof(server_addr_)),
    port_(port),
    sock_fdesc_init_(0),
    sock_fdesc_conn_(0) {
  client_len_ = server_addr_size_;
}

void SocketServer::ConnectToNetwork() {
  ML_LOG(Info, "ConnectToNetwork() - 1");
  // Initialize Socket
  sock_fdesc_init_ = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fdesc_init_ == -1) {
    close(sock_fdesc_init_);
    ML_LOG(Info, "Couldn't create socket!");
    exit(1);
  }
  ML_LOG(Info, "ConnectToNetwork() - 2");
  // Zero out server address struct
  memset((char*)&server_addr_, 0, server_addr_size_);

  // Set server address struct
  server_addr_.sin_family = AF_INET;
  server_addr_.sin_addr.s_addr = INADDR_ANY;
  server_addr_.sin_port = htons(port_);
  ML_LOG(Info, "ConnectToNetwork() - 3");
  // Assign server address to initial socket file descriptor
  if (bind(sock_fdesc_init_, (struct sockaddr*)&server_addr_,
           server_addr_size_) == -1) {
    ML_LOG(Error, "Couldn't bind initial socket file descriptor!");
    ML_LOG(Info, "Trying again after killing existing process on port: %d", port_);
    close(sock_fdesc_init_);
    if (bind(sock_fdesc_init_, (struct sockaddr*)&server_addr_,
             server_addr_size_) == -1) {
      ML_LOG(Error, "Couldn't bind initial socket file descriptor after retry!");
      exit(1);
    }
    ML_LOG(Info, "Successful bind to port %d after killing previous process", port_);
  }
  ML_LOG(Info, "ConnectToNetwork() - 4");
  // Enable listening on initial socket file descriptor
  listen(sock_fdesc_init_, 5);
  ML_LOG(Info, "ConnectToNetwork() - 5");
  // Block process until connection with client has been established.
  // 'client_fdesc' set as new file descriptor to be used for communication
  sock_fdesc_conn_ = accept(sock_fdesc_init_, (struct sockaddr*)&client_addr_,
                            &client_len_);
  if (sock_fdesc_conn_ == -1) {
    ML_LOG(Error, "ERROR! Client couldn't connect!");
    exit(1);
  }
  ML_LOG(Info, "ConnectToNetwork() - 6");
  ML_LOG(Info, "Listening to port %d", port_);
}

void SocketServer::ReceiveImageDims() {

  ssize_t bytes_sent = 0;
  size_t dims_size = 0;

  size_t sizeof_dims = sizeof(image_height_);

  if (bytes_sent = recv(sock_fdesc_conn_, (char*)&image_width_, sizeof_dims, 0) == -1) {
    ML_LOG(Error, "ERROR!: recv failed");
    ML_LOG(Error, "sock_fdesc: %d, image_size: %zu, bytes_sent: %zu", 
      sock_fdesc_conn_, dims_size, bytes_sent);
    exit(1);
  }
  else {
      ML_LOG(Error, "Image dimensions: [%d]", image_width_);
    }

  if (bytes_sent = recv(sock_fdesc_conn_, (char*)&image_height_, sizeof_dims, 0) == -1) {
    ML_LOG(Error, "ERROR!: recv failed");
    ML_LOG(Error, "sock_fdesc: %d, image_size: %zu, bytes_sent: %zu", 
      sock_fdesc_conn_, dims_size, bytes_sent);

    exit(1);
  }
  ML_LOG(Info, "Image dimensions: [%dx%d]", image_height_, image_width_);
  if (bytes_sent = recv(sock_fdesc_conn_, (char*)&image_channels_, sizeof_dims, 0) == -1) {
    ML_LOG(Error, "ERROR!: recv failed");
    ML_LOG(Error, "sock_fdesc: %d, image_size: %zu, bytes_sent: %zu", 
      sock_fdesc_conn_, dims_size, bytes_sent);

    exit(1);
  }

  ML_LOG(Info, "Image dimensions: [%dx%dx%d]", 
    image_height_, image_width_, image_channels_);
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
      ML_LOG(Error, "ERROR!: recv failed");
          ML_LOG(Error, "i: %d, sock_fdesc: %d, image_size: %d, num_bytes: %d", 
            i, sock_fdesc_conn_, image_size, num_bytes);

      exit(1);
    }
  }

  // ML_LOG(Info, "image_size: %d, total_num_bytes: %d", image_size, total_num_bytes);
  *data = sock_data;
}

SocketServer::~SocketServer()
{
  close(sock_fdesc_init_);
  ML_LOG(Info, "Closed socket at port %d", port_);    
}
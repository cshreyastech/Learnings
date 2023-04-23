#include <memory> // unique_ptr
#include <sys/stat.h>

#include "client_server/server/socket_server.hpp"
#include <iostream>


// bool DirExists(const char* path) {
//   struct stat info;
//   if (stat(path, &info) != 0) {
//     perror("Can't access path");
//     return 0;
//   }
//   else if(info.st_mode & S_IFDIR) {
//     return 1;
//   }
//   else return 0;
// }

void AssertCond(bool assert_cond, const char* fail_msg) {
  if (!assert_cond) {
    // printf("Error: %s\nUsage: ./pic-server <port> <out_path>\n", fail_msg);
    printf("Error: %s\nUsage: ./pic-server <port>\n", fail_msg);
    exit(1);
  }
}

void ParseArgs(int argc, char** argv) {
  // AssertCond(argc == 3, "Wrong number of arguments");
  AssertCond(argc == 2, "Wrong number of arguments");
  // AssertCond(DirExists(argv[2]), "Supplied directory does not exist");
}

int main(int argc, char** argv) {
  ParseArgs(argc, argv);
  int port = atoi(argv[1]);
  // std::unique_ptr<SocketServer> server_ptr(new SocketServer(port, argv[2]));
  std::unique_ptr<SocketServer> server_ptr(new SocketServer(port));
  server_ptr->ConnectToNetwork();
  server_ptr->ReceiveImageDims();

  // while(1) {
  //   cv::Mat image;
  //   server_ptr->ReceiveImageBoy(image);
  //   server_ptr->ShowImage(image);
  // }

  unsigned char* data;
  server_ptr->ReceiveTextureData(&data);
  
  return 1; // Should not return
}

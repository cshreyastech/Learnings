#include <memory> // unique_ptr
#include <sys/stat.h>

#include <opencv2/core.hpp> // Mat

#include "toy/socket_server.hpp"
#include <iostream>

std::string type2str(int type) {
  std::string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

bool DirExists(const char* path) {
  struct stat info;
  if (stat(path, &info) != 0) {
    perror("Can't access path");
    return 0;
  }
  else if(info.st_mode & S_IFDIR) {
    return 1;
  }
  else return 0;
}

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
  while(1) {
    cv::Mat image;
    server_ptr->ReceiveImageBoy(image);
    server_ptr->ShowImage(image);
  }

  // cv::Mat image;
  // // server_ptr->ReceiveImage(image);
  // server_ptr->ReceiveImageBoy(image);
  // std::cout << "Boy Image Data type = " << type2str(image.type()) << std::endl;
  // std::cout << "Boy Image Dimensions = " << image.size() << std::endl;

  // // server_ptr->WriteImage(image);
  // server_ptr->ShowImage(image);
  // server_ptr->DestroyAllWindows();
  
  return 1; // Should not return
}

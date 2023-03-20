#include "toy/socket_client.hpp"

#include <memory> // unique_ptr
#include <cstdlib> // atoi

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
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


void GenerateImage(int rows, int cols, cv::Mat& image) {
  int lol = 0;
  image = cv::Mat::zeros(rows, cols, CV_8UC3);
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      int idk = (lol % 23 == 0) ? rand() % 255 : 35;
      image.at<cv::Vec3b>(row, col)[0] = idk;
      image.at<cv::Vec3b>(row, col)[1] = idk;
      image.at<cv::Vec3b>(row, col)[2] = idk;
      lol += 7;
    }
  }
}

void AssertCond(bool assert_cond, const char* fail_msg) {
  if (!assert_cond) {
    // printf("Error: %s\nUsage: ./pic-client <port> <rows> <cols>\n", fail_msg);
    printf("Error: %s\nUsage: ./pic-client <ip> <port>\n", fail_msg);
    exit(1);
  }
}

void ParseArgs(int argc, char** argv) {
  AssertCond(argc == 3, "Wrong number of arguments");
}

int main(int argc, char** argv) {
  ParseArgs(argc, argv);
  
  std::string hostname = argv[1]; 
  int port = atoi(argv[2]);
  // int cols = atoi(argv[2]);
  // int rows = atoi(argv[3]);

  std::string imagePath = "../boy.jpg";

  // Read image in Grayscale format
  cv::Mat boy_image = cv::imread(imagePath, 1);
  std::cout << "Boy Image Data type = " << type2str(boy_image.type()) << std::endl;
  std::cout << "Boy Image Dimensions = " << boy_image.size() << std::endl;

  int cols = boy_image.cols; //480;
  int rows = boy_image.rows;// 360;
  // const char hostname[] = "localhost";
  std::unique_ptr<SocketClient> client_ptr(new SocketClient(hostname.c_str(), port));
  client_ptr->ConnectToServer();
  client_ptr->SendImageDims(cols, rows);
  // while (1) {
  //   cv::Mat image;
  //   GenerateImage(cols, rows, image);
  //   client_ptr->SendImage(image);
  // }

  cv::Mat image;
  // GenerateImage(cols, rows, image);
  
  // std::cout << "Data type = " << type2str(image.type()) << std::endl;
  // std::cout << "Image Dimensions = " << image.size() << std::endl;




  // client_ptr->SendImage(image);
  // client_ptr->SendImage(image);
  client_ptr->SendImage(boy_image);
  client_ptr->SendImage(boy_image);

  return 1; // Should not return
}

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

using namespace cv;
using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[256];
  // if (argc < 3) {
  //    fprintf(stderr,"usage %s hostname port\n", argv[0]);
  //    exit(0);
  // }
  portno = atoi("8080");
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) 
      error("ERROR opening socket");
  server = gethostbyname("127.0.0.1");
  if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, 
       (char *)&serv_addr.sin_addr.s_addr,
       server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
      error("ERROR connecting");

  Mat image;
  // image = imread(argv[3], CV_LOAD_IMAGE_COLOR);
  image = imread("../boyGray.jpg", IMREAD_COLOR);
  if(! image.data )                              // Check for invalid input
  {
    cout <<  "Could not open or find the image" << std::endl ;
    return -1;
  }

  Mat frame;
  // frame = (frame.reshape(0,1)); // to make it continuous

  int  imgSize = frame.total()*frame.elemSize();

  int bytes = -1;
  // Send data here
  bytes = send(sockfd, frame.data, imgSize, 0);
  if (n < 0) 
   error("ERROR writing to socket");

  // n = write(sockfd,image.data,image.total()*image.channels());
  // if (n < 0) 
  //   error("ERROR writing to socket");

  
  close(sockfd);

  namedWindow( "Client", WINDOW_AUTOSIZE );// Create a window for display.
  imshow( "Client", image );  
  waitKey(0);
  return 0;
}
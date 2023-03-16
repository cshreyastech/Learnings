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
  exit(1);
}

int main(int argc, char *argv[])
{
   int sockfd, newsockfd, portno;
   socklen_t clilen;
   char buffer[1024];
   struct sockaddr_in serv_addr, cli_addr;
   int n;
   // if (argc < 2) {
   //     fprintf(stderr,"ERROR, no port provided\n");
   //     exit(1);
   // }
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) 
      error("ERROR opening socket");
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = atoi("8080");
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   if (bind(sockfd, (struct sockaddr *) &serv_addr,
      sizeof(serv_addr)) < 0) 
    error("ERROR on binding");
   
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   newsockfd = accept(sockfd, 
               (struct sockaddr *) &cli_addr, 
               &clilen);
   if (newsockfd < 0) 
      error("ERROR on accept");
   bzero(buffer,1024);

   n = read(newsockfd,buffer,1023);
   if (n < 0) error("ERROR reading from socket");

   Mat image(690,690,CV_8UC3,*buffer);
   // imwrite("/home/securitas/images/prova.jpg",image);
   close(newsockfd);
   close(sockfd);

   namedWindow( "Server", WINDOW_AUTOSIZE );// Create a window for display.
   imshow( "Server", image );  
   waitKey(0);
   return 0;
}
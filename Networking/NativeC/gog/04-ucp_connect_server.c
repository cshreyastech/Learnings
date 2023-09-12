// server program for udp connection
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include <iostream>

#define PORT 5000
#define MAXLINE 1000
// g++ -std=c++17 04-ucp_connect_server.c -o 04-ucp_connect_server

// Driver code
int main()
{
	char buffer[100];
	// char *message = "Hello Client";
  std::string message = "Hello from Server";

	unsigned int listenfd, len;
	struct sockaddr_in servaddr, cliaddr;
	bzero(&servaddr, sizeof(servaddr));

	// Create a UDP Socket
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	// bind server address to socket descriptor
	// bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

  printf("listenfd:%d, sizeof(servaddr): %ld\n", listenfd, sizeof(servaddr));
  if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
    perror("Couldn't bind initial socket file descriptor after retry!");
    exit(1);
  }
  printf("Successful bind to port after killing previous process\n");





	
	//receive the datagram
	len = sizeof(cliaddr);
	int n = recvfrom(listenfd, buffer, sizeof(buffer),
			0, (struct sockaddr*)&cliaddr,&len); //receive message from server
	buffer[n] = '\0';
	puts(buffer);
		
	// send the response
	sendto(listenfd, message.c_str(), MAXLINE, 0,
		(struct sockaddr*)&cliaddr, sizeof(cliaddr));
}

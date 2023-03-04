/* A simple server in the internet domain using TCP
	The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	if(argc < 2) {
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}

	int sockfd, newsockfd, portno, n;
	char buffer[255];

	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen;
	
	/*
	struct sockaddr {
		sa_family_t sa_family;
		char sa_data[14];
	};
	returns 
	0 -> success
	1-> failure
	*/
	

	// socket(domain, type, protocol)
	// AF_INET - IPv4
	// SOCK_STREAM - TCP, SOCK_DGRAM - UDP
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		error("ERROR opening socket");

	// Clear buffer
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	// int bind(int sockfd, const struct sockaddr *adr, socklen_t addrlen)
	if(bind(sockfd, (struct sockaddr *) &serv_addr,
		sizeof(serv_addr)) < 0)
		error("ERROR on binding");

	/* int listen(int sockfd, int backlog)
		listens for socket in a connection
	*/
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	/*
	newsockfd = accept(sockfd, 
		(struct sockaddr *) &addr,
		&addrlen);
	*/
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if(newsockfd < 0)
		error("Error on Accept");
	/*
	int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	*/

	while(1)
	{
		bzero(buffer, 255);
		n = read(newsockfd, buffer, 255);
		if(n < 0)
			error("Error on reading");
		printf("Client: %s\n", buffer);
		bzero(buffer, 255);

		fgets(buffer, 255, stdin);
		n = write(newsockfd, buffer, strlen(buffer));
		if(n < 0)
			error("Error on writing");

		int i = strncmp("Bye", buffer, 3);
		if(i == 0)
			break;
	}
	// int read(newsockfd, buffer, buffer_size);
	// int write(newsockfd, buffer, buffer_size);

	close(newsockfd);
	close(sockfd);
	return 0;
}
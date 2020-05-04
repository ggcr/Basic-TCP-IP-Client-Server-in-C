#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>

#define SEND_BUFFER_SIZE 2048

int client(char *server_ip, char *server_port) {
 	
	int s, bytes;

	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
	}

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	inet_pton(AF_INET, server_ip, &(server.sin_addr));
	server.sin_port = htons(atoi(server_port));

	if(connect(s, (struct sockaddr *)&server, sizeof server) < 0){
		perror("connect");
	}

	char* buffer = malloc(SEND_BUFFER_SIZE * sizeof(char));

	int total = 0;
	bzero(buffer, SEND_BUFFER_SIZE);
	int bufsize = SEND_BUFFER_SIZE;
	
	fgets(buffer,SEND_BUFFER_SIZE,stdin);
	
	while(total < bufsize){
		if((bytes = send(s, buffer + total, bufsize , 0)) < 0)
			perror("send");
		total += bytes;
		bufsize -= bytes;
	}
	free(buffer);
	return 0;
}

int main(int argc, char **argv) {
  char *server_ip;
  char *server_port;

  if (argc != 3) {
    fprintf(stderr, "Usage: ./client-c [server IP] [server port] < [message]\n");
    exit(EXIT_FAILURE);
  }

  server_ip = argv[1];
  server_port = argv[2];
  return client(server_ip, server_port);
}

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

#define QUEUE_LENGTH 10
#define RECV_BUFFER_SIZE 2048

int server(char *server_port) {
	
	int s, new_s, bytes, bufsize;
	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
	}

	struct sockaddr_in server, client;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(server_port));
	
	if(bind(s, (struct sockaddr *)&server, sizeof(server))){
		perror("bind");
	}

	if(listen(s, QUEUE_LENGTH) < 0) {
		perror("listen");
	}

	socklen_t size_client = sizeof(client);
	if((new_s = accept(s, (struct sockaddr *)&client, &size_client)) < 0){
		perror("accept");
	}

	char* buffer = malloc(RECV_BUFFER_SIZE * sizeof(char));

	bufsize = RECV_BUFFER_SIZE;

	bytes = recv(new_s, buffer, bufsize, 0);
	while((bufsize - bytes) > 0){
		bufsize -= bytes;
		if((bytes = recv(new_s, buffer + bytes, bufsize - bytes, 0)) < 0){
			perror("recv");
		}	
	}


	printf("%s\n", buffer );
	free(buffer);

	return 0;
}

int main(int argc, char **argv) {
  char *server_port;

  if (argc != 2) {
    fprintf(stderr, "Usage: ./server-c [server port]\n");
    exit(EXIT_FAILURE);
  }

  server_port = argv[1];
  return server(server_port);
}

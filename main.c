#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]) {
  int socket_server = socket(PF_INET, SOCK_STREAM, 0);
  struct sockaddr_in  my_addr;
  int client_socket;
  FILE *f;

  if (socket_server == -1) {
    printf("error when creating a socket");
    exit(EXIT_FAILURE);
  }

  memset(&my_addr, 0, sizeof(my_addr));
  my_addr.sin_family = AF_INET; // family address to ipv4
  my_addr.sin_port = htons(8080);
  my_addr.sin_addr.s_addr = INADDR_ANY;

  if(bind(socket_server, (struct sockaddr*)&my_addr, sizeof(my_addr)) == -1) {
    printf("error when binding a socket");
    exit(EXIT_FAILURE);
  }

  if (listen(socket_server, 5) == -1) {
    printf("error when listeninig in a socket");
    exit(EXIT_FAILURE); 
  }

  while (1) {
    client_socket = accept(socket_server, NULL, NULL);
    if (client_socket == -1) {
      printf("error when accepting connection in socket");
      exit(EXIT_FAILURE);
    }

    f = fopen("index.html", "r");
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), f)) {
      write(client_socket, buffer, strlen(buffer));
    }
  }

  fclose(f);
  close(client_socket);

  printf("exit binding the socket to port 8080");
}

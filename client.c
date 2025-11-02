#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int client_socket;

  while(1) {
    // int connect(int sockfd, const struct sockaddr *addr,
                   // socklen_t addrlen);   
    int socket_client = socket(PF_INET, SOCK_STREAM, 0);
    int bytesRead;
    struct sockaddr_in my_addr;

    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(8080);
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while(1) {
      int success = connect(socket_client,(struct sockaddr*) &my_addr, sizeof(my_addr));
      char buff[1024];

      while((bytesRead = read(socket_client, buff, sizeof(buff)))) {
        printf("%s", buff);
      } 
    }

    

  }
}

/*
  Program that opens a socket and assings it to the tcp server ip from the rs232wifi card
*/
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void){
  int s = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in server;
  if(s == -1){
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(8899);
  if(inet_pton(AF_INET, "10.10.100.254", &server.sin_addr) <= 0){
    perror("inet_pton");
    exit(EXIT_FAILURE);
  }

  if(connect(s, (struct sockaddr*)&server, sizeof(server)) < 0){
    perror("connect");
    close(s);
    exit(EXIT_FAILURE);
  }
  char buffer[100] = {"Test"};
  write(s, buffer, strlen(buffer));
  printf("Connected");
}


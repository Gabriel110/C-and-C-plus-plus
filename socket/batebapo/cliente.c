#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netdb.h>
#define PORT "3333"
#define LEN 1024
#define SERVER_ADDR "127.0.0.1"

//messagen de erro
void errors(char *msg){
  fprintf(stderr,"%s: %s\n",msg,strerror(errno));
  exit(1);
}

int open_socket_dns(char *host,char *port){
  struct addrinfo *res;
  struct addrinfo hints;
  memset(&hints,0,sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  if(getaddrinfo(host,port,&hints,&res) == -1){
    errors("Can`t resolve the address");
  }
  int d_sock = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
  if(d_sock == -1){
    errors("Can`t opem socket");
  }
  int c = connect(d_sock,res->ai_addr,res->ai_addrlen);
  if(c == -1){
    errors("Can`t connect to socket");
  }
  return d_sock;
}

int say(int socket, char*msg){
  int result = send(socket,msg,strlen(msg),0);
  if(result == -1){
    fprintf(stderr,"%s: %s\n","Error telking to the server",strerror(errno));
  }
  return result;
}

int connect_to_server(int socket,struct sockaddr *server){
  int c = connect(socket,(struct sockaddr*)server,sizeof(server));
  return c;
}

int main(){
  struct sockaddr_in server;
  int sockfd;
  int len = sizeof(server);
  int slen;
  char buffer_in[LEN];
  char buffer_out[LEN];
  fprintf(stdout, "Starting Client ...\n");

  int d_sock = open_socket_dns(SERVER_ADDR,PORT);
  if(slen = recv(d_sock,buffer_in,LEN,0) > 0){
    buffer_in[slen + 1] = '\0';
    fprintf(stdout, "Server says: %s\n", buffer_in);
  }
  while(1){
    memset(buffer_in,0x0,LEN);
    memset(buffer_out,0x0,LEN);
    fprintf(stdout, "Say something to the server: ");
    fgets(buffer_out, LEN, stdin);
    say(d_sock,buffer_out);
    slen = recv(d_sock,buffer_in,LEN,0);
    printf("Server answer: %s\n", buffer_in);
    if(strcmp(buffer_in, "bye") == 0)
      break;
  }
  close(sockfd);
  fprintf(stdout, "\nConnection closed\n\n");
  return EXIT_SUCCESS;
}
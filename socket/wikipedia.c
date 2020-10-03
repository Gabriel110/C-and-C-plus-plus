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
#define PORT 3333

//messagen de erro
void errors(char *msg){
  fprintf(stderr,"%s: %s\n",msg,strerror(errno));
  exit(1);
}
//abre socket pela url
int open_socket(char *host,char *port){
  struct addrinfo *res;
  struct addrinfo hints;
  memset(&hints,0,sizeof(hints));
  hints.ai_family = PF_UNSPEC;
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
int main(int argc, char *argv[]){
  int d_sock;
  d_sock = open_socket("en.wikipedia.org","80");
  char buff[255];
  sprintf(buff,"GET /wiki/%s http/1.1\r\n",argv[1]);
  say(d_sock,buff);

  say(d_sock,"Host: en.wikipedia.org\r\n\r\n");
  char rec[256];
  int bytesRcvd = recv(d_sock,rec,255,0);
  while(bytesRcvd){
    if(bytesRcvd == -1)
      errors("Can`t read from server");
    rec[bytesRcvd] = '\0';
    printf("%s",rec);
    bytesRcvd = recv(d_sock,rec,255,0);
  }
  close(d_sock);
  return 0;
}
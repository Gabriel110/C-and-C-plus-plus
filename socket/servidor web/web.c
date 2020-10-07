#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>

#define HOST "127.0.0.1"
#define PORT 3333
#define MAX 1024

char webpage[] =
"HTTP/3.0 200 OK\r\n"
"Content-Type: text/html; charset=utf-8\r\n\r\n"
"<!DOCTYPE html>\r\n"
"<html lang='pt-br'><head><meta charset='UTF-8'><title>Gabriel</title></head>\r\n"
"<body><h1>Ola mundo!</h1></body>\n\r"
"</html>\r\n";

int mensage_erro(char* msg){
  fprintf(stderr,"%s: %s\n",msg,strerror(errno));
  exit(1);
}

int open_socket_connect(char *host,char *port){
  struct addrinfo *res;
  struct addrinfo hints;
  memset(&hints,0,sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if(getaddrinfo(host,port,&hints,&res) == -1)
    mensage_erro("Não foi prossivel pegar o host");

  int d_sock = socket(res->ai_family,res->ai_socktype,res->ai_protocol);

  if(d_sock == -1)
    mensage_erro("Não foi prossivel criar o socket");
  
  int c = connect(d_sock,res->ai_addr,res->ai_addrlen);

  freeaddrinfo(res);

  if( c == -1) mensage_erro("Erro ao conectar");
  return d_sock;
}

int open_sock(){
  int s = socket(AF_INET,SOCK_STREAM,0);
  if(s == -1) mensage_erro("Erro ao criar o socket!");
  return s;
}

void bind_to_port(int socket,int port){
  struct sockaddr_in name;
  name.sin_family = AF_INET;
  name.sin_addr.s_addr = htonl(INADDR_ANY);
  name.sin_port = htons(PORT);
  int reuse = 1;
  if(setsockopt(socket,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,(char*)&name,sizeof(int)) == -1)
    fprintf(stderr,"Erro no eruse");
  int b = bind(socket,(struct sockaddr*)&name,sizeof(name));
  if(b == -1)mensage_erro("Erro no bind");
}


int main(int argv, char*argc[]){
  struct sockaddr_storage client_addr;
  int addr_len = sizeof(client_addr);
  char buff[MAX];
  int fd_server,fd_client;
  fd_server = open_sock();
  bind_to_port(fd_server,PORT);
  if(listen(fd_server,10) == -1) mensage_erro("Erro do listem");

  while(1){
    fd_client = accept(fd_server,(struct sockaddr*)&client_addr,&addr_len);
    if(fd_client == -1){
      perror("Falha na conexao");
      continue;
    }
    printf("Cliente conectado");
    if(!fork()){
      close(fd_server);
      memset(buff,0,MAX);
      recv(fd_client,buff,MAX,0);
      printf("%s\n",buff);
      send(fd_client,webpage,sizeof(webpage)-1,0);
    }
    close(fd_client);
  }
  
  return 0;
}
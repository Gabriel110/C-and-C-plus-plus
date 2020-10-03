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
#define BUFFER 4096

//messagen de erro
void errors(char *msg){
  fprintf(stderr,"%s: %s\n",msg,strerror(errno));
  exit(1);
}
int open_socket(){
  int s = socket(AF_INET,SOCK_STREAM,0);
  if(s == -1){
    errors("Não foi possivel crirar o socket");
  }
  return s;
}
void bind_to_port(int socket,int port){
  struct sockaddr_in name;
  name.sin_family = AF_INET;
  name.sin_addr.s_addr = htonl(INADDR_ANY);
  name.sin_port = htons(PORT);
  int reuse = 1;
  if(setsockopt(socket,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,(char*)&reuse,sizeof(int))==-1){
    fprintf(stderr,"Error reuse");
  }
  int b = bind(socket,(struct sockaddr*)&name,sizeof(name));
  if(b == -1){
    errors("Bind não feito");
  }
}

int say(int socket, char*msg){
  int result = send(socket,msg,strlen(msg),0);
  if(result == -1){
    fprintf(stderr,"%s: %s\n","Error telking to the server",strerror(errno));
  }
  return result;
}

int main(int argc, char* argv[]){

  struct sockaddr_storage client_addr;
  int serverfd, clientfd;
  char buffer[BUFFER];
  serverfd = open_socket();
  fprintf(stdout, "Server socket created with fd: %d\n", serverfd);
  bind_to_port(serverfd,PORT);

  if(listen(serverfd,10)==-1){
    errors("Listen error:");
  }
  fprintf(stdout, "Listening on port %d\n", PORT);
  socklen_t client_len = sizeof(client_addr);
  if((clientfd = accept(serverfd,(struct sockaddr*)&client_addr,&client_len)) == -1){
    errors("Accept error:");
  }

  strcpy(buffer, "Hello, client!\n\0");
  if(say(clientfd,buffer)){
    fprintf(stdout, "Client connected.\nWaiting for client message ...\n");
  }
  do{
    memset(buffer,0x0,BUFFER);
    int mensage_len;
    if(mensage_len = recv(clientfd, buffer, BUFFER, 0) > 0){
      printf("Client says: %s\n", buffer);
    };
    if(strcmp(buffer, "bye") == 0) {
      say(clientfd, "bye");
    } else {
      say(clientfd, "yep\n");
    }
  }while(strcmp(buffer, "bye"));
  close(clientfd);
  close(serverfd);
  return EXIT_SUCCESS;
}
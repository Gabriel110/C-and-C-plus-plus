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
#define PORT 3333

//messagen de erro
void errors(char *msg){
  fprintf(stderr,"%s: %s\n",msg,strerror(errno));
  exit(1);
};

//cria um socket
int opem_listener_socket(){
  int listener_d = socket(AF_INET,SOCK_STREAM,0);
  if( listener_d == -1)
    errors("Can`t opem socket");
  return listener_d;
};

void bind_to_port(int socket, int port){
  struct sockaddr_in name;
  name.sin_family = AF_INET;
  name.sin_port = htons(port);
  name.sin_addr.s_addr = htonl(INADDR_ANY);
  int reuse = 1;

  if(setsockopt(socket,SOL_SOCKET,SO_REUSEADDR,(char*)&reuse,sizeof(int)) == 1)
    errors("Can`t set the reuse iption on the socket");
  
  int c = bind(socket,(struct sockaddr*)&name,sizeof(name));
  if( c == -1)
    errors("Can`t bind to socket");
};

//trantando a mensagem enviado do cliente
int read_in(int socket,char* buf, int len){
  char *s = buf;
  int slen = len;
  int c = recv(socket, s, slen, 0);
  if((c > 0)  && (s[c-1]!='\n')){
    s += c;
    slen -= c;
    c = recv(socket, s, slen,0);;
  };

  if(c < 0){
    return c;
  }else if(c == 0){
    buf[0] = '\0';
  }else{
    s[c-1]!='\0';
  }

  return len - slen;
};

int say(int socket, char *s){
  int result = send(socket,s,strlen(s),0);
  if(result == -1)
    fprintf(stderr,"%s %s","Error talking to the client",strerror(errno));
  return result;
};
int listener_d ;

int catch_signal(int sig, void (*handler)(int)){
  struct sigaction actions;
  actions.sa_handler = handler;
  sigempty(&actions.sa_mask);
  actions.sa_flags = 0;
  return sigaction(sig,&actions,NULL);
}

void handle_shutdown(int sig){
  if(listener_d)
    close(listener_d);
  fprintf(stderr,"Bye!\n");
  exit(0);
}

int main(){
  if(catch_signal(SIGINT, handle_shutdown) == -1){
    errors("Can`t set the interrupt handle");
  }
  //ciando socket
  listener_d = opem_listener_socket();
  //connectando o socke a porta
  bind_to_port(listener_d,3333);

  if(listen(listener_d,10) == -1){
     errors("Can`t listener");
  }

  struct sockaddr_storage client_addr;
  unsigned int addr_len = sizeof(client_addr);
  char buf[255];

  while(1){
    int connet_d = accept(listener_d,(struct sockaddr*)&client_addr,&addr_len);
    if(connet_d == -1){
       errors("Can`t open secondary socket");
    }

    if(say(connet_d,"Ola bem vindo ao meu servidor!\n")){
      read_in(connet_d,buf,sizeof(buf));
      if(strncasecmp("Who`s there?",buf,12)){
        say(connet_d,"You shoud say 'Who's there?'!");
      }
    }else{

    }
    close(connet_d);
  }
  return 0;
}
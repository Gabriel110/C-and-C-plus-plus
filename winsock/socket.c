#include <winsock2.h>
#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define PORT 3333
#define H0ST 1222222 

void menssage_erro(char *msg){
  fprintf(stderr,"%s: %s",msg,strerror(errno));
  exit(1);
}

int create_sock(){
  int s = socket(AF_INET,SOCK_STREAM,0);
  if( s == -1){
    menssage_erro("Erro ao cria o socket");
  }
  return s;
}

void conected_bind_port(int socket,int port,int host){
  struct sockaddr_in name;
  name.sin_family = AF_INET;
  name.sin_addr.s_addr =host;
  name.sin_port = port;
  int reuse = 1;

  if(setsockopt(socket,SOL_SOCKET,SO_REUSEADDR,(char*)&reuse,sizeof(int)) == -1){
    menssage_erro("Erro no reuse");
  }

  int b = bind(socket,(struct sockaddr*)&name, sizeof(name));
  if( b == -1){
    menssage_erro("Erro no bind");
  }
}

int say(int socket, char *msg){
  int result = send(socket,msg,strlen(msg),0);
  if(result < 0){
    printf("Nao a mensagem!");
  }
  return result;
}

int read_in(int socket,char *buff, int len){
  char *s = buff;
  int slen = len;
  int c = recv(socket,s,slen,0);
  if(( c > 0) && (s[c-1] != '\n')){
    s += c;
    slen -= c;
  }

  if(c < 0){
    return c;
  }else if(c == 0){
    buff[0] = '\0';
  }else{
    s[c-1] = '\0'; 
  }
  return len - slen;
}

int main(int argc,char *argv[]){
  int socket_addr;
  struct sockaddr_in name;
  WSADATA  dados;
  //inicia a dll do win
  if(WSAStartup(MAKEWORD(2,0),&dados) == SOCKET_ERROR){
    
  }
  //alocando meu socket
  socket_addr = create_sock();
  struct sockaddr_storage  addr;
  int addr_size = sizeof(addr);
  conected_bind_port(socket_addr,PORT,INADDR_ANY);
  //memset(&(name.sin_zero),0,Cool);
  listen(socket_addr,10);
  puts("Conected ..");
  char buf[255];

  while(1){
    int connet_d = accept(socket_addr,(struct sockaddr*)&addr,&addr_size);
    if(connet_d == -1){
      menssage_erro("Can`t open secondary socket");
    }
    if(say(connet_d,"Ola bem vindo ao meu servidor!\n")){
      read_in(connet_d,buf,sizeof(buf));
      if(strncasecmp("Who`s there?",buf,12)){
        say(connet_d,"You shoud say 'Who's there?'!");
      }
    }else{

    }
    //isso ira destruir a conexao e liberar a memoria.
    closesocket(socket_addr);
    //limpamdo a estrutura WSA
    WSACleanup();
  }

 
  return 0;
}
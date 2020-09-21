#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORT 3333

int main(){

   char *adivice[] = {
    "Como se chama um pedido de desculpas escrito em pontos e traços? Código re-Morse.",
    "Eu ia contar uma piada de viagem no tempo, mas vocês não gostaram…",
    "Que raça de cachorro salta mais alto que um prédio? Qualquer uma, porque prédio não pula.",
    "Como se chama o cachorro do mágico? Labracadabrador.",
    "O que o tubarão disse quando comeu o peixe-palhaço? Que gosto engraçado!",
    "Porque coalas não são ursos de verdade? Porque eles não têm as coalificações.",
    "Qual a tecla preferida do astronauta? A da barra de espaço." 
  };


 

  struct sockaddr_in servidor_addr;
  struct sockaddr_storage cliente_addr;
  int addr_len = sizeof(cliente_addr);
  int listener_d;
  int reuse = -1;
   //IPV6 TCP 0
  listener_d = socket(AF_INET,SOCK_STREAM,0);

  if(setsockopt(listener_d,SOL_SOCKET,SO_REUSEADDR,(char*)&reuse,sizeof(int)) == -1){
    perror("Erro no reuse socket");
   
  }

  servidor_addr.sin_family = AF_INET;
  servidor_addr.sin_port = htons(PORT);
  servidor_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if(bind(listener_d,(struct sockaddr*)&servidor_addr,sizeof(servidor_addr)) == -1){
    perror("Erro no bind");
    exit(EXIT_FAILURE);
  };

  listen(listener_d,10);
  puts("conectando ..");
  while(1){
    int connection_d = accept(listener_d,(struct sockaddr*)&cliente_addr,&addr_len);
    char *msg = adivice[rand()%5];
    send(connection_d,msg,strlen(msg),0);
    close(connection_d);
  }
  return 0;
}
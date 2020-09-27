#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

void error(char *msg){
  fprintf(stderr,"%s: %s\n",msg,strerror(errno));
  exit(1);
}

int main(int argc,char *argv[]){
  char *urls[] = {"https://www.inovacaotecnologica.com.br/boletim/rss.xml"};
  FILE *f = fopen("stories.txt","r+");
  fseek(f,0,SEEK_END);
  if(!f){
    FILE *f = fopen("stories.txt","w+");
    error("Stories.txt criado, tente novamente");
  }
  //cria um processo filho
  pid_t pid = fork();

  //se ouver um erro responda
  if(pid == -1){
    error("Can´t for process");
  }
  //se não for o pai
  if(!pid){
    //muda a saida padrão para aquivo de texto
    if(dup2(fileno(f),1) == -1){
      error("Can´t redrect Standared Output!");
    }
    //chamada de sistema para um script python
    if(execl("/usr/bin/python3","/usr/bin/python3","./rss/rss.py",urls[0],NULL) == -1){
      error("Can´t run script");
    }
    
  }
  fclose(f);
  return 0;
}
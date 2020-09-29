#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

void error(char *msg){
  fprintf(stderr,"%s: %s\n",msg,strerror(errno));
  exit(1);
}

void open_url(char*url){
  char laucher[255];
  sprintf(laucher,"cmd /c start %s",url);
  system(laucher);

  sprintf(laucher,"x-www-browser '%s' &",url);
  system(laucher);

  sprintf(laucher,"open %s",url);
  system(laucher);
}

int main(int argc,char *argv[]){
  char *urls[] = {"https://www.inovacaotecnologica.com.br/boletim/rss.xml"};
  FILE *f = fopen("stories.txt","r+");
  fseek(f,0,SEEK_END);
  if(!f){
    FILE *f = fopen("stories.txt","w+");
    error("Stories.txt criado, tente novamente");
  }
  int fd[2];

  if(pipe(fd)==-1){
    error("Não foi possivel criar o pipe");
  }
  //cria um processo filho
  pid_t pid = fork();

  //se ouver um erro responda
  if(pid == -1){
    error("Can´t for process");
  }
  //se não for o pai
  if(!pid){
    //Configura a saida padrão para a ponta de escrita do pipe
    dup2(fd[1],1);
    //O filho não vai ler o pipe
    close(fd[0]);
    //muda a saida padrão para aquivo de texto
    // if(dup2(fileno(f),1) == -1){
    //   error("Can´t redrect Standared Output!");
    // }
    //chamada de sistema para um script python
    if(execl("/usr/bin/python3","/usr/bin/python3","./rss/rss.py",urls[0],NULL) == -1){
      error("Can´t run script");
    }
  }
  int pid_status;
  //impede que o processo pai feche antes que seu filho termine a tarefa
  if(waitpid(pid,&pid_status,0) == -1){
    error("Erro no ao gravar aquivios");
  }
  //Isso vai redirecionar a entrada padrão para ponta de leitura do pipe
  dup2(fd[0],0);
  //fecha a porta de leitura do pipe
  close(fd[1]);
  
  char line[255];
  while(fgets(line,255,stdin)){
    if(line[0] == '\t')
       open_url(line +1);
  }
  fclose(f);
  return 0;
}
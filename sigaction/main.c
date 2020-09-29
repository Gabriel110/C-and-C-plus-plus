#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void diediedie(int sig){
  puts("Adeus o mundo cruel ...");
  exit(1);
}

int catch_signal(int sig,void(*handler)(int)){
  //strutura de sigaction
  struct sigaction action;
  action.sa_handler = handler;//função a ser chamado
  sigemptyset(&action.sa_mask);//mascara
  action.sa_flags = 0;//flags

  return sigaction(sig,&action,NULL);
}

int main(int argv, char*argc[]){
  if(catch_signal(SIGINT,diediedie)){
    fprintf(stderr,"Can`t map the handler");
    exit(2);
  }
  char name[30];
  printf("Enter your name: ");
  fgets(name,30,stdin);
  printf("Helo %s",name);
  return 0;
}
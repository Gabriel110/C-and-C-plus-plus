#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//pegando a hr atual
char *now(){
  time_t t;
  time(&t);
  return asctime(localtime(&t));
}

int main(){
  char comment[80];
  char cmd[128];

  fgets(comment, 80, stdin);
  sprintf(cmd,"echo '%s %s' >> reports.log", comment, now());

  system(cmd);
  return 0;
}
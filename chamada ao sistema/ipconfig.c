#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){
  if(execlp("/sbin/ifconfig","/sbin/ifconfig",NULL) == -1){
    if(execlp("ipconfig","ipconfig",NULL) == -1){
      fprintf(stderr,"Cannot run ipconfig: %s",strerror(errno));
      return 1;
    }
  }
  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define count 4

char *casais[]={
    "brenda e bruno",
    "marta e kel",
    "fernanda e marcos",
    "bruno e bruna"
};

void find(){
  int i;
  puts("Search results: ");
  for(i=0; i < count; i++){
    if(strstr(casais[i],"brenda") && strstr(casais[i],"bruno"))
      printf("%s\n",casais[i]);
  }
}

int main(){
  find();
}
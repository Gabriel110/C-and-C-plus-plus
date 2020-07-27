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

int FernadaMarcos(char *s){
  return strstr(s,"fernanda") || strstr(s,"marcos");
}

int BrunoBrenda(char *s){
  return strstr(s,"brenda") && strstr(s,"bruno");
}

//ponteiro para funcao
//tipo de retorno int
//nome para variavel ponteiro (*match)
//tipo de paramento (char*)
//int(*match)(char*)
void find(int(*macth)(char*)){
  int i;
  puts("Search results: ");
  puts("-------------------------");
  for(i=0; i < count; i++){
    if(macth(casais[i]))
      printf("%s\n",casais[i]);
  }
  puts("-------------------------");
}

int main(){
  //nesse caso match aponta para funcao BrunoBrenda()
  find(BrunoBrenda);
   //nesse caso match aponta para funcao FernadaMarcos()
  find(FernadaMarcos);
}
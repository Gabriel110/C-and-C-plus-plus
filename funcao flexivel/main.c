#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void printfln(char args, ...){
//usado pra armazenar parametros adicionais passado na funcao
  va_list string;
//diz onde o parametro vai começar
  va_start(string, args);
  for(int i = 0; i < args; i++){
    printf("String: %c\n",va_arg(string, char*));
  }
  va_end(string);
}

void soma(int num, ...){
  int resultado = 0;
  //guarda os parametros passado na funcao
  va_list nums;
  //iniciando 
  va_start(nums, num);
  for(int i = 0; i < num; i++){
    //imprimindo
    resultado += va_arg(nums, int);
    printf("Soma: %d\n",resultado);
  }
  //terminando
  va_end(nums);
}

int main(){
  printfln(3,'A','B','C');
  soma(3,2,3,1);
}
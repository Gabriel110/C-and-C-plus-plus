#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_ARRAY 1

typedef struct{
  char name[200];
  int idade;
  float salario;
}funcionarios;
funcionarios func[TAM_ARRAY];
int main(){
 
//inicianado fun com valores nulos
  for(int i = 0;i < TAM_ARRAY; i++){
    strcpy(func[i].name,"NULL");
    func[i].idade = 0;
    func[i].salario = 0.0;
  }
//preenchendo o array
  for(int i = 0;i < TAM_ARRAY; i++){
    printf("Qual nome do %d funcionario: ",i);
    scanf("%s%*c",&func[i].name);
    printf("Qual e a idade do %d funcionario: ",i);
    scanf("%d%*c",&func[i].idade);
    printf("Qual e o salario do %d funcionarios: ",i);
    scanf("%f%*c",&func[i].salario);
  }
//imprimido array
  puts("FUNCIONARIOS");
  for(int i = 0;i < TAM_ARRAY; i++){
   printf("Nome: %s\nIdade: %d\nSalario: %2.f\n",func[i].name,func[i].idade,func[i].salario);
  }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct island{
  char *name;
  // char *opens;
  // char *closes;
  struct island *next;
}island;

//imprimindo as ilhas
void display(island *start){
  island *i = start;
  for(;i!=NULL;i = i->next){
    printf("Name: %s\n"/*Opens: %s\nCloses: %s\n"*/,i->name/*,i->opens,i->closes*/);
  }
}

//criando ilhas pegando so o nome
island *createIsland(char *name){
  island *i = malloc(sizeof(island));
  i->name = strdup(name);
  // i->opens = "13:00";
  // i->closes = "17:00";
  i->next = NULL;
  return i;
}

//liberando a memoria
void ralease(island *start){
  island *i = start;
  island *next = NULL;
  for(;i!=NULL;i=next){
    next = i->next;
    free(i->name);
    free(i);
  }
}

int main(){
  //tudo começa com null
  island *start = NULL;
  island *i = NULL;
  island *next = NULL;
  //pegando o nome 
  char name[80];
  for(;fgets(name,80,stdin)!= NULL;i=next){
    //proximo sempre sera o nova ilha
    next = createIsland(name);
    //se a lista de ilhas forem vazia start e next que a primeira ilha
    if(start == NULL){
       start = next;
    }
    //se i estiver ocupado passe para o proximo, e cria uma nova ilha
    if(i != NULL){
      i->next = next;
    }
  }

  display(start);
  ralease(start);
}

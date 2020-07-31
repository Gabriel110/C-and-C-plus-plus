#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

//tipo de dado pesonalisado
typedef struct{
  int id;
}DataNode;
//crinado no com referencia ao proximo
typedef struct{
  DataNode data;
  struct Node *next;
}Node;
//cruiando lista
typedef struct{
  int size;
  Node *head;
}List;

List *create_list(){
  //alocando espaco para lista
  List* list = (List*)malloc(sizeof(List));
  //setando size como zero e cabeca como null
  list->size = 0;
  list->head = NULL;
  return list;
};

int main(){
  List * lista = create_list();
  printf("%d",lista->size);
}
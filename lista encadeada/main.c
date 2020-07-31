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

void push(List* list, DataNode data){
  //alocando memoria
  Node* node = (Node*)malloc(sizeof(Node));
  //atribuindo o dado ao no
  node->data = data;
  //fazendo next que e null virar a cabeca
  node->next = list->head;
  //colocando o no na cabeaca
  list->head = node;
  //aumentando o tamanho da lista
  list->size++;
};

int main(){
  List * lista = create_list();
  DataNode data = {5};
  push(lista, data);
  printf("%d",lista->head->data.id);
}
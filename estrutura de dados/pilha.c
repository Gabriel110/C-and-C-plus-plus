#include <stdlib.h>
#include <stdio.h>


typedef struct node {
  struct node *next;
  int value;
}Node;

typedef struct stack{
  Node * top;
  int size;
}Stack;

Stack * start(){
  Stack * s = malloc(sizeof(Stack));
  s->top = NULL;
  s->size = 0;
  return s;
}

int empty(Stack *s){
  return s->size == 0;
}


void printStack(Node *top){
  while (top){
    printf("|%d|\n", top->value);
    top = top->next;
  }
}

void push(Stack *s, int value){
  Node *n = malloc(sizeof(Node));
  n->next = s->top;
  n->value = value;
  s->top = n;
  s->size += 1;
}

int pop(Stack *s){
  Node *n;
  int value;

  if(!empty(s)){

    n = s->top;
    value = n->value;
    s->top = s->top->next;

    s->size -= 1;
    free(n);
    n = NULL;

    return value;
  }else{
    printf("Vazia!");
    return 0;
  }
}

int main(){
  Stack *s = start();

  push(s, 16);
  push(s, 15);
  push(s, 14);
  push(s, 13);
  push(s, 12);
  push(s, 11);


  printStack(s->top);
  printf("pop-> |%d|\n", pop(s));
  printStack(s->top);

}
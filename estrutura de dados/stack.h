typedef struct stack{
  Node * top;
  int size;
}Stack;

Stack * startStack(){
  Stack *stack = malloc(sizeof(Stack));
  stack->top = NULL;
  stack->size = 0;
  return stack;
}

int isEmpty(Stack *stack){
  return stack->size == 0;
}

void pushStack(Stack *stack, char value){
  Node *node = malloc(sizeof(Node));
  node->next = stack->top;
  node->value = value;
  stack->top = node;
  stack->size += 1;
}

char pop(Stack *stack){
  Node *node;
  char value;
  if(!isEmpty(stack)){
    node =  stack->top;
    value = node->value;
    stack->top = stack->top->next;
    stack->size -= 1;
    free(node);
    return value;
  }else{
    printf("Stack is empty");
    return '0';
  }
}

void printStack(Node *top){
  while (top){
    printf("%c\n", top->value);
    top = top->next;
  }
}

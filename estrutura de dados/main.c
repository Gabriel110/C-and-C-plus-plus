#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "stack.h"
#include "queue.h"


void testStack(){
  Stack *stack = startStack();

  pushStack(stack,'c');
  pop(stack);
  pushStack(stack,'d');
  pushStack(stack,'e');
  printStack(stack->top);

}


int main(){
  testStack();
  return 0;
}
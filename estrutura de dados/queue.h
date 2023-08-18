typedef struct queue{
  struct node *head;
  struct node *syrup;
  int size;
}Queue;


Queue *startQueue(){
  Queue * queue = malloc(sizeof(Queue));
  queue->size = 0;
  queue->head = NULL;
  queue->syrup = NULL;
  return queue;
}

void enqueue(Queue *queue, char value){
  Node *node = malloc(sizeof(Node));
  node->value = value;
  node->next = NULL;
  if(queue->syrup != NULL){
    queue->syrup->next = node;
  }else {
    queue->head = node;
  }
  queue->syrup = node;
  queue->size+=1;
}

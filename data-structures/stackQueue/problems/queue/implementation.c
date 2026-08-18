// queue implementation in C

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct QNode {
  int value;
  struct QNode *next;
} QNode;

typedef struct {
  QNode *front;
  QNode *back;
  size_t size;
} Queue;

void queueInit(Queue *queue) {
  queue->front = NULL;
  queue->back = NULL;
  queue->size = 0;
}

void queueClear(Queue *queue) {
  QNode *curr = queue->front;
  while (curr != NULL) {
    QNode *old = curr;
    curr = curr->next;
    free(old);
  }
  queueInit(queue);
}

static QNode* queueNewNode(int value) {
  QNode *ptr = (QNode *)malloc(sizeof(QNode));
  if (ptr == NULL) return NULL;
  ptr->value = value;
  ptr->next = NULL;
  return ptr;
}

bool queueEnqueue(Queue *queue, int value) {
  QNode *newNode = queueNewNode(value);
  if (newNode == NULL) return false;
  if (queue->size == 0) {
    queue->front = newNode;
    queue->back = newNode;
  } else {
    QNode *oldBack = queue->back;
    oldBack->next = newNode;
    queue->back = newNode;
  }
  queue->size++;
  return true;
}

bool queueDequeue(Queue *queue, int *outValue) {
  if (queue->size == 0) return false;
  QNode *oldFront = queue->front;
  if (queue->size == 1) {
    queue->back = NULL;
    queue->front = NULL;
  } else {
    queue->front = queue->front->next;
  }
  if (outValue != NULL) *outValue = oldFront->value;
  free(oldFront);
  queue->size--;
  return true;
}

bool queuePeek(Queue *queue, int *outValue) {
  if (queue->front != NULL) {
    if (outValue != NULL) *outValue = queue->front->value;
  } else return false;
  return true;
}

bool queueIsEmpty(Queue *queue) {
  if (queue->size == 0) return true;
  return false;
}

int main(void) {
  Queue queue;
  int value = 0;

  queueInit(&queue);
  printf("After init -> empty: %s size: %zu\n",
         queueIsEmpty(&queue) ? "true" : "false", queue.size);

  printf("Enqueue 10 -> %s\n", queueEnqueue(&queue, 10) ? "ok" : "fail");
  printf("Enqueue 20 -> %s\n", queueEnqueue(&queue, 20) ? "ok" : "fail");
  printf("Enqueue 30 -> %s\n", queueEnqueue(&queue, 30) ? "ok" : "fail");
  printf("Size after enqueues: %zu\n", queue.size);

  if (queuePeek(&queue, &value)) {
    printf("Peek -> %d\n", value);
  } else {
    printf("Peek failed (queue empty)\n");
  }

  while (queueDequeue(&queue, &value)) {
    printf("Dequeue -> %d (size now %zu)\n", value, queue.size);
  }

  printf("Queue empty after dequeues? %s\n",
         queueIsEmpty(&queue) ? "true" : "false");

  queueClear(&queue);
  printf("After clear -> empty: %s size: %zu\n",
         queueIsEmpty(&queue) ? "true" : "false", queue.size);

  return 0;
}


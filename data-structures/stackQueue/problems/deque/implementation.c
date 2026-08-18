// Double-ended queue implemented with a doubly linked list.
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct DequeNode {
  int value;
  struct DequeNode *prev;
  struct DequeNode *next;
} DequeNode;

typedef struct {
  DequeNode *front;
  DequeNode *back;
  size_t size;
} Deque;

void dequeInit(Deque *deque) {
  deque->front = deque->back = NULL;
  deque->size = 0;
}

static DequeNode *dequeNewNode(int value) {
  DequeNode *node = (DequeNode *)malloc(sizeof(DequeNode));
  if (node == NULL) return NULL;
  node->value = value;
  node->prev = node->next = NULL;
  return node;
}

bool dequePushFront(Deque *deque, int value) {
  DequeNode *node = dequeNewNode(value);
  if (node == NULL) return false;
  node->next = deque->front;
  if (deque->front) deque->front->prev = node;
  else deque->back = node;
  deque->front = node;
  deque->size++;
  return true;
}

bool dequePushBack(Deque *deque, int value) {
  DequeNode *node = dequeNewNode(value);
  if (node == NULL) return false;
  node->prev = deque->back;
  if (deque->back) deque->back->next = node;
  else deque->front = node;
  deque->back = node;
  deque->size++;
  return true;
}

bool dequePopFront(Deque *deque, int *out) {
  if (deque->front == NULL) return false;
  DequeNode *node = deque->front;
  if (out) *out = node->value;
  deque->front = node->next;
  if (deque->front) deque->front->prev = NULL;
  else deque->back = NULL;
  free(node);
  deque->size--;
  return true;
}

bool dequePopBack(Deque *deque, int *out) {
  if (deque->back == NULL) return false;
  DequeNode *node = deque->back;
  if (out) *out = node->value;
  deque->back = node->prev;
  if (deque->back) deque->back->next = NULL;
  else deque->front = NULL;
  free(node);
  deque->size--;
  return true;
}

void dequeClear(Deque *deque) {
  int ignored;
  while (dequePopFront(deque, &ignored)) {}
}

int main(void) {
  Deque deque;
  int value;
  dequeInit(&deque);
  dequePushBack(&deque, 20);
  dequePushFront(&deque, 10);
  dequePushBack(&deque, 30);
  dequePopFront(&deque, &value);
  printf("Front pop: %d\n", value);
  dequePopBack(&deque, &value);
  printf("Back pop: %d\n", value);
  dequeClear(&deque);
  return 0;
}


#include <bits/stdc++.h>
using namespace std;

typedef struct SNode {
  int value;
  struct SNode *next;
} SNode;

typedef struct {
  SNode *top;
  size_t size;
} Stack;

void stackInit(Stack *stack) {
  stack->top = nullptr;
  stack->size = 0;
}

void stackClear(Stack *st) {
  SNode *curr = st->top;
  while (curr != NULL) {
    SNode *next = curr->next;
    free(curr);
    curr = next;
    st->size--;
  }
  st->top = nullptr;
}

bool stackPush(Stack *st, int n) {
  SNode *newEl = (SNode *)malloc(sizeof(SNode));
  if (newEl == nullptr)
    return false;
  newEl->value = n;
  newEl->next = st->top;
  st->top = newEl;
  st->size++;
  return true;
}

bool stackPop(Stack *st, int *n) {
  if (st->size == 0)
    return false;
  if (n != nullptr) {
    *n = st->top->value;
  }
  SNode *oldEl = st->top;
  st->top = st->top->next;
  st->size--;
  free(oldEl);
  return true;
}

bool stackPeek(Stack *st, int *n) {
  if ((n != nullptr) && (st->size != 0)) {
    *n = st->top->value;
    return true;
  } else {
    return false;
  }
}

bool stackIsEmpty(Stack *st) {
  if (st->size == 0)
    return true;
  return false;
}

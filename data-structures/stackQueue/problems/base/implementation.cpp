/**
 * LIFO stack implemented with linked nodes. Push, pop, and peek all run in O(1).
 */
// stack implementation in C

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
  stack->top = NULL;
  stack->size = 0;
}

void stackClear(Stack *stack) {
  while (stack->top != NULL) {
    SNode *next = stack->top->next;
    free(stack->top);
    stack->top = next;
    stack->size--;
  }
}

static SNode *stackNewNode(int value) {
  SNode *ptr = (SNode *)malloc(sizeof(SNode));
  if (ptr == NULL) return NULL;
  ptr->value = value;
  ptr->next = NULL;
  return ptr;
}

bool stackPush(Stack *stack, int value) {
  SNode *newNode = stackNewNode(value);
  if (newNode == NULL) return false; 
  newNode->next = stack->top;
  stack->top = newNode;
  stack->size++;
  return true;
}

bool stackPop(Stack *stack, int *outValue) {
  if (stack->top == NULL) return false;
  if (outValue != NULL) *outValue = stack->top->value;
  SNode *newTop = stack->top->next;
  free(stack->top);
  stack->top = newTop;
  stack->size--;
  return true;
}

bool stackPeek(Stack *stack, int *outValue) {
  if (stack->top == NULL) return false;
  if (outValue != NULL) *outValue = stack->top->value;
  return true;
}

bool stackIsEmpty(Stack *stack) {
  if (stack->size == 0) return true;
  return false;
}

int main(void) {
  Stack stack;
  int value = 0;

  stackInit(&stack);
  printf("After init: empty=%s size=%zu\n",
         stackIsEmpty(&stack) ? "true" : "false", stack.size);

  printf("Push 10 -> %s\n", stackPush(&stack, 10) ? "ok" : "fail");
  printf("Push 20 -> %s\n", stackPush(&stack, 20) ? "ok" : "fail");
  printf("Push 30 -> %s\n", stackPush(&stack, 30) ? "ok" : "fail");
  printf("Size after pushes: %zu\n", stack.size);

  if (stackPeek(&stack, &value)) {
    printf("Peek: %d\n", value);
  } else {
    printf("Peek failed (stack empty)\n");
  }

  while (stackPop(&stack, &value)) {
    printf("Pop -> %d (size now %zu)\n", value, stack.size);
  }

  printf("Stack empty after pops? %s\n", stackIsEmpty(&stack) ? "true" : "false");

  stackClear(&stack);
  printf("After clear: empty=%s size=%zu\n",
         stackIsEmpty(&stack) ? "true" : "false", stack.size);

  return 0;
}

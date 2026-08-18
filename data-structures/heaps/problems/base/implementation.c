// Priority Queue implementation in C

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
  int *data;
  size_t size;
  size_t cap;
  bool isMinHeap;
} PQueue;

bool pqInit(PQueue *pq, size_t initialCapacity, bool isMinHeap) {
  pq->data = (int *)malloc(initialCapacity * sizeof(int));
  pq->size = 0;
  pq->cap = initialCapacity;
  pq->isMinHeap = isMinHeap;
  return true;
}

void pqClear(PQueue *pq) {
  free(pq->data);
  pq->data = NULL;
  pq->size = 0;
  pq->cap = 0;
}

static bool pqEnsureCapacity(PQueue *pq) {
    if (pq->size < pq->cap) {
        return true;                     // still room
    }

    size_t newCap = pq->cap ? pq->cap * 2 : 8; // default bootstrap size
    int *newData = realloc(pq->data, newCap * sizeof *pq->data);
    if (!newData) {
        return false;                    // leave pq untouched on OOM
    }

    pq->data = newData;
    pq->cap = newCap;
    return true;
}

static inline size_t parent(size_t i) { return (i-1)/2; }
static inline size_t lChild(size_t i) { return (2*i) + 1; }
static inline size_t rChild(size_t i) { return (2*i) + 2; }

static bool pqCompare(PQueue *pq, int a, int b) {
  if (pq->isMinHeap) {
    return a < b ? true : false;
  } else {
    return a >= b ? true : false;
  }
}

static void pqSiftUp(PQueue *pq, size_t index) {
  int curr = index;
  while (curr > 0) {
    int currVal = pq->data[curr];
    int parentVal = pq->data[parent(curr)];
    bool valHeap = pqCompare(pq, parentVal, currVal);
    if (!valHeap) {
      pq->data[parent(curr)] = currVal;
      pq->data[curr] = parentVal;
      curr = parent(curr);
    } else break;
  }
}

static void pqSiftDown(PQueue *pq, size_t index) {
  int curr = index;
  int left = lChild(curr);
  while (left < pq->size) {
    int leftVal = pq->data[left];
    int right = rChild(curr);
    int rightVal = pq->data[right];
    int bestChild = left;
    if ((right < pq->size) && (pqCompare(pq, rightVal, leftVal))) bestChild = right;
    int currVal = pq->data[curr];
    int childVal = pq->data[bestChild];
    bool valHeap = pqCompare(pq, currVal, childVal);
    if (!valHeap) {
      pq->data[bestChild] = currVal;
      pq->data[curr] = childVal;
      curr = bestChild;
    } else break;
    left = lChild(curr);
  }
}

bool pqPush(PQueue *pq, int value) {
  if (pqEnsureCapacity(pq)) {
    pq->data[pq->size] = value;
    pq->size++;
    pqSiftUp(pq, pq->size-1);
    return true;
  } else return false;
}

bool pqPop(PQueue *pq, int *outValue) {
  if (pq->size > 0) {
    if (outValue != NULL) *outValue = pq->data[0];
    pq->data[0] = pq->data[pq->size-1];
    pq->size--;
    pqSiftDown(pq, 0);
    return true;
  } else return false;
}

bool pqPeek(PQueue *pq, int *outValue) {
  if (pq->size > 0) {
    if (outValue != NULL) {
      *outValue = pq->data[0];
    }
    return true;
  } else return false;
}

bool pqIsEmpty(PQueue *pq) {
  return pq->size == 0;
}

int main(void) {
    PQueue pq;
    if (!pqInit(&pq, 4, false)) {
        fprintf(stderr, "pqInit failed\n");
        return 1;
    }

    int values[] = {30, 10, 25, 5, 40, 15, 123, 12323, 1, 33,34534};
    size_t count = sizeof values / sizeof *values;

    for (size_t i = 0; i < count; ++i) {
        if (!pqPush(&pq, values[i])) {
            fprintf(stderr, "pqPush failed at %zu\n", i);
            pqClear(&pq);
            return 1;
        }
    }

    int peek = 0;
    if (pqPeek(&pq, &peek)) {
        printf("Peek: %d\n", peek);
    }

    while (!pqIsEmpty(&pq)) {
        int out = 0;
        pqPop(&pq, &out);
        printf("%d ", out);
    }
    printf("\n");

    pqClear(&pq);
    return 0;
}


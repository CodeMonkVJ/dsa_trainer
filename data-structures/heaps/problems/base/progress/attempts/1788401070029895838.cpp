#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
using namespace std;

typedef struct {
  int *data;
  size_t size;
  size_t cap;
  bool isMinHeap;
} PQueue;

bool pqInit(PQueue *pq, size_t cap, bool isMinHeap) {
  pq->data = (int *)malloc(sizeof(int) * cap);
  if (pq->data == nullptr)
    return false;
  pq->size = 0;
  pq->cap = cap;
  pq->isMinHeap = isMinHeap;
  return true;
}

void pqClear(PQueue *pq) {
  free(pq->data);
  pq->data = nullptr;
  pq->size = 0;
  pq->cap = 4;
}

bool pqPush(PQueue *pq, int v) {
  if (pq->size >= pq->cap / 2) {
    pq->cap *= 2;
    int *newData = (int *)realloc(pq->data, pq->cap * sizeof(int));
    if (newData == nullptr)
      return false;
    pq->data = newData;
  }
  pq->data[pq->size] = v;
  pq->size++;
  int idx = pq->size - 1;
  while (idx > 0) {
    int parent = (idx - 1) / 2;
    if (pq->isMinHeap) {
      if (pq->data[parent] > pq->data[idx]) {
        int tmp = pq->data[parent];
        pq->data[parent] = pq->data[idx];
        pq->data[idx] = tmp;
        idx = parent;
      } else
        break;
    } else {
      if (pq->data[parent] < pq->data[idx]) {
        int tmp = pq->data[parent];
        pq->data[parent] = pq->data[idx];
        pq->data[idx] = tmp;
        idx = parent;
      } else
        break;
    }
  }
  return true;
}

bool pqPop(PQueue *pq, int *v) {
  if (v == nullptr)
    return false;

  if (pq->size == 0)
    return false;

  *v = pq->data[0];
  pq->data[0] = pq->data[pq->size - 1];
  pq->size--;

  if (pq->size <= pq->cap / 4) {
    int *newData = (int *)realloc(pq->data, (pq->cap / 2) * sizeof(int));
    if (newData == nullptr)
      return false;
    pq->data = newData;
    pq->cap /= 2;
  }

  int idx = 0;
  while (true) {
    int parent = pq->data[idx];
    int child1Idx = idx * 2 + 1, child2Idx = idx * 2 + 2, child1Val, child2Val;
    if (child1Idx < pq->size)
      child1Val = pq->data[idx * 2 + 1];
    if (child2Idx < pq->size)
      child2Val = pq->data[idx * 2 + 2];

    if (child1Idx >= pq->size && child2Idx >= pq->size)
      break;
    if (child1Idx >= pq->size || child2Idx >= pq->size) {
      int childIdx = child1Idx >= pq->size ? child2Idx : child1Idx;
      int childVal = child1Idx >= pq->size ? child2Val : child1Val;
      if (pq->isMinHeap) {
        if (parent > childVal) {
          pq->data[idx] = childVal;
          pq->data[childIdx] = parent;
          idx = childIdx;
        } else
          break;
      } else {
        if (parent < childVal) {
          pq->data[idx] = childVal;
          pq->data[childIdx] = parent;
          idx = childIdx;
        } else
          break;
      }
    } else {
      int childIdx, childVal;
      if (pq->isMinHeap) {
        childVal = min(child1Val, child2Val);
        childIdx = child1Val > child2Val ? child2Idx : child1Idx;
        if (parent > childVal) {
          pq->data[idx] = childVal;
          pq->data[childIdx] = parent;
          idx = childIdx;
        } else
          break;
      } else {
        childVal = max(child1Val, child2Val);
        childIdx = child1Val < child2Val ? child2Idx : child1Idx;
        if (parent < childVal) {
          pq->data[idx] = childVal;
          pq->data[childIdx] = parent;
          idx = childIdx;
        } else
          break;
      }
    }
  }

  return true;
}

bool pqPeek(PQueue *pq, int *v) {
  if (v == nullptr)
    return false;
  if (pq->size == 0)
    return false;
  *v = pq->data[0];
  return true;
}

bool pqIsEmpty(PQueue *pq) {
  if (pq->size == 0)
    return true;
  else
    return false;
}

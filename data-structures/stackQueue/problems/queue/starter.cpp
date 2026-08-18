#include <bits/stdc++.h>
using namespace std;
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
  queue->front = queue->back = nullptr;
  queue->size = 0;
}
void queueClear(Queue *) {}
bool queueEnqueue(Queue *, int) { return false; }
bool queueDequeue(Queue *, int *) { return false; }
bool queuePeek(Queue *, int *) { return false; }
bool queueIsEmpty(Queue *) { return true; }

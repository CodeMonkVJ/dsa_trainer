#include <bits/stdc++.h>
using namespace std;

typedef struct Node {
  int value;
  struct Node *prev;
  struct Node *next;
} Node;

typedef struct {
  Node *head;
  Node *tail;
  size_t size;
} DList;

void dlInit(DList *dl) {
  dl->head = dl->tail = nullptr;
  dl->size = 0;
}

void dlClear(DList *dl) {
  while (dl->head != nullptr) {
    Node *old = dl->head;
    dl->head = dl->head->next;
    free(old);
  }
  dl->tail = nullptr;
  dl->size = 0;
}

bool dlPushFront(DList *dl, int v) {
  Node *oldHead = dl->head;
  dl->head = (Node *)malloc(sizeof(Node));
  if (dl->head == nullptr)
    return false;
  if (dl->size == 0) {
    dl->tail = dl->head;
  }
  dl->head->prev = nullptr;
  dl->head->next = oldHead;
  if (oldHead != nullptr)
    oldHead->prev = dl->head;
  dl->head->value = v;
  dl->size++;
  return true;
}

bool dlPushBack(DList *dl, int v) {
  Node *oldTail = dl->tail;
  dl->tail = (Node *)malloc(sizeof(Node));
  if (dl->tail == nullptr)
    return false;
  if (dl->size == 0) {
    dl->head = dl->tail;
  }
  dl->tail->next = nullptr;
  dl->tail->prev = oldTail;
  if (oldTail != nullptr)
    oldTail->next = dl->tail;
  dl->tail->value = v;
  dl->size++;
  return true;
}

bool dlInsertAt(DList *dl, size_t i, int v) {
  if (i == 0)
    return dlPushFront(dl, v);
  if (i == dl->size)
    return dlPushBack(dl, v);
  if (i > dl->size)
    return false;

  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == nullptr)
    return false;
  Node *curr = dl->head;
  newNode->value = v;

  while (i--) {
    curr = curr->next;
  }

  Node *prev = curr->prev;
  prev->next = newNode;
  newNode->prev = prev;
  newNode->next = curr;
  curr->prev = newNode;
  dl->size++;

  return true;
}

bool dlPopFront(DList *dl, int *v) {
  if (dl->size == 0)
    return false;
  if (dl->size == 1) {
    *v = dl->head->value;
    dlClear(dl);
    return true;
  }
  Node *newHead = dl->head->next;
  newHead->prev = nullptr;
  *v = dl->head->value;
  free(dl->head);
  dl->size--;
  dl->head = newHead;
  return true;
}

bool dlPopBack(DList *dl, int *v) {
  if (dl->size == 0)
    return false;
  if (dl->size == 1) {
    *v = dl->head->value;
    dlClear(dl);
    return true;
  }
  Node *newTail = dl->tail->prev;
  newTail->next = nullptr;
  *v = dl->tail->value;
  free(dl->tail);
  dl->size--;
  dl->tail = newTail;
  return true;
}

bool dlEraseAt(DList *dl, size_t i, int *v) {
  if (dl->size == 0)
    return false;
  if (i == 0)
    return dlPopFront(dl, v);
  if (i == dl->size - 1)
    return dlPopBack(dl, v);

  Node *curr = dl->head;
  while (i--) {
    curr = curr->next;
  }

  Node *prev = curr->prev;
  Node *next = curr->next;
  prev->next = next;
  next->prev = prev;
  *v = curr->value;

  free(curr);
  dl->size--;

  return true;
}

Node *dlFind(DList *dl, int v) {
  Node *curr = dl->head;
  while (curr != nullptr) {
    if (curr->value == v)
      break;
    curr = curr->next;
  }
  return curr;
}

int dlAt(DList *dl, size_t i) {
  if (dl->size == 0 || i >= dl->size)
    return -1;
  Node *curr = dl->head;
  while (i--) {
    curr = curr->next;
  }

  return curr->value;
}

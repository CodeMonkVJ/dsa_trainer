/**
 * Doubly linked list supporting constant-time end operations and indexed traversal. Node links make insertion/removal at a known node O(1).
 */
// doubly linked list implementation in C

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

void dlInit(DList *list) {
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}

void dlFreeNode(Node *node) {
  node->prev = NULL;
  node->next = NULL;
  node->value = 0;
  free(node);
}

void dlClear(DList *list) {
  Node *curr = list->tail;
  while (curr != NULL) {
    Node *prev = curr->prev;
    dlFreeNode(curr);
    curr = prev;
    list->size--;
  }
  list->head = NULL;
  list->tail = NULL;
}

static Node* dlNewNode(int value) {
  Node *ptr = (Node *)malloc(sizeof(Node));
  if (ptr == NULL) {
    return NULL;
  }
  ptr->value = value;
  ptr->prev = NULL;
  ptr->next = NULL;
  return ptr;
}

bool dlPushFront(DList *list, int value) {
  Node *newNode = dlNewNode(value);
  if (newNode == NULL) return false;
  if (list->head == NULL) {
    list->head = newNode; 
    list->tail = newNode;
    list->size = 1;
    return true;
  }
  Node *oldHead = list->head;
  newNode->next = oldHead;
  oldHead->prev = newNode;
  list->head = newNode;
  list->size++;
  return true;
}

bool dlPushBack(DList *list, int value) {
  Node *newNode = dlNewNode(value);
  if (newNode == NULL) return false;
  if (list->tail == NULL) {
    list->head = newNode; 
    list->tail = newNode;
    list->size = 1;
    return true;
  }
  Node *oldTail = list->tail;
  newNode->prev = oldTail;
  oldTail->next = newNode;
  list->tail = newNode;
  list->size++;
  return true;
}

bool dlInsertAt(DList *list, size_t index, int value) {
  if (index > list->size) return false;
  if (index == 0) {
    return dlPushFront(list, value);
  }
  if (index == list->size) {
    return dlPushBack(list, value);
  }

  Node *curr = list->head;
  for (size_t i=0;i<index;i++) {
    if (curr == NULL) return false;
    curr = curr->next;
  }

  Node *prevNode = curr->prev;
  Node *newNode = dlNewNode(value);
  if (newNode == NULL) return false;
  
  prevNode->next = newNode;
  newNode->prev = prevNode;
  newNode->next = curr;
  curr->prev = newNode;
  list->size++;
  return true;
}

bool dlPopFront(DList *list, int *outValue) {
  if (list->size == 0) return false;
  Node *popNode = list->head;
  if (list->size == 1) {
    list->head = NULL;
    list->tail = NULL;
  } else {
    Node *newHead = popNode->next;
    newHead->prev = NULL;
    list->head = newHead;
  }
  list->size--;
  if (outValue != NULL) *outValue = popNode->value;
  dlFreeNode(popNode);
  return true;
}

bool dlPopBack(DList *list, int *outValue) {
  if (list->size == 0) return false;
  Node *popNode = list->tail;
  if (list->size == 1) {
    list->head = NULL;
    list->tail = NULL;
  } else {
    Node *newTail = popNode->prev;
    newTail->next = NULL;
    list->tail = newTail;
  }
  list->size--;
  if (outValue != NULL) *outValue = popNode->value;
  dlFreeNode(popNode);
  return true;
}

bool dlEraseAt(DList *list, size_t index, int *outValue) {
  if (index >= list->size) return false;
  if (index == 0) {
    return dlPopFront(list, outValue);
  }
  if (index == list->size - 1) {
    return dlPopBack(list, outValue);
  }
  Node *curr = list->head;
  for (size_t i=0;i<index;i++) {
    if (curr == NULL) return false;
    curr = curr->next;
  }
  Node *prevNode = curr->prev;
  Node *nextNode = curr->next;
  prevNode->next = nextNode;
  nextNode->prev = prevNode;
  if (outValue != NULL) *outValue = curr->value;
  dlFreeNode(curr);
  list->size--;
  return true;
}

Node* dlFind(DList *list, int value) {
  Node *curr = list->head;
  while (curr != NULL) {
    int val = curr->value;
    if (val == value) return curr;
    curr = curr->next;
  }
  return NULL;
}

int dlAt(DList *list, size_t index) {
  if (index >= list->size) return -123123;
  int iter = index;
  Node *curr = list->head;
  while (iter--) {
    if (curr != NULL) curr = curr->next;
    else break;
  }
  if (curr != NULL) {
    return curr->value;
  } else return -123123;
}

// driver code to check

int main(void) {
  DList list;
  int out = 0;

  printf("Manual doubly linked list checks\n");
  dlInit(&list);
  printf("After init -> size: %zu\n", list.size);

  printf("PushBack 10: %s\n", dlPushBack(&list, 10) ? "ok" : "fail");
  printf("PushBack 20: %s\n", dlPushBack(&list, 20) ? "ok" : "fail");
  printf("PushFront 5: %s\n", dlPushFront(&list, 5) ? "ok" : "fail");
  printf("Current size: %zu\n", list.size);

  printf("Values via dlAt:\n");
  for (size_t i = 0; i < list.size; ++i) {
    printf("  index %zu -> %d\n", i, dlAt(&list, i));
  }

  printf("Insert value 15 at index 2: %s\n", dlInsertAt(&list, 2, 15) ? "ok" : "fail");
  printf("After insert values:\n");
  for (size_t i = 0; i < list.size; ++i) {
    printf("  index %zu -> %d\n", i, dlAt(&list, i));
  }

  if (dlPopFront(&list, &out)) {
    printf("PopFront value: %d\n", out);
  } else {
    printf("PopFront failed\n");
  }

  if (dlPopBack(&list, &out)) {
    printf("PopBack value: %d\n", out);
  } else {
    printf("PopBack failed\n");
  }

  if (dlEraseAt(&list, 1, &out)) {
    printf("EraseAt index 1 -> %d\n", out);
  } else {
    printf("EraseAt index 1 failed\n");
  }

  Node *found = dlFind(&list, 15);
  printf("Find value 15 -> %s\n", found != NULL ? "found" : "not found");

  printf("Remaining values:\n");
  for (size_t i = 0; i < list.size; ++i) {
    printf("  index %zu -> %d\n", i, dlAt(&list, i));
  }

  dlClear(&list);
  printf("After clear -> size: %zu\n", list.size);

  return 0;
}

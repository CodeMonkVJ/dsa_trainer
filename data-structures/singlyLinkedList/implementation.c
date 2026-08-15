// Singly linked list with insertion, deletion, search, and reversal.
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *next;
} Node;

typedef struct {
  Node *head;
  size_t size;
} SinglyLinkedList;

void listInit(SinglyLinkedList *list) {
  list->head = NULL;
  list->size = 0;
}

bool listPushFront(SinglyLinkedList *list, int value) {
  Node *node = (Node *)malloc(sizeof(Node));
  if (node == NULL) return false;
  node->value = value;
  node->next = list->head;
  list->head = node;
  list->size++;
  return true;
}

bool listInsertAfter(Node *node, int value) {
  if (node == NULL) return false;
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) return false;
  newNode->value = value;
  newNode->next = node->next;
  node->next = newNode;
  return true;
}

bool listRemoveFirst(SinglyLinkedList *list, int value) {
  Node **link = &list->head;
  while (*link != NULL && (*link)->value != value) link = &(*link)->next;
  if (*link == NULL) return false;
  Node *removed = *link;
  *link = removed->next;
  free(removed);
  list->size--;
  return true;
}

Node *listFind(SinglyLinkedList *list, int value) {
  for (Node *node = list->head; node != NULL; node = node->next)
    if (node->value == value) return node;
  return NULL;
}

void listReverse(SinglyLinkedList *list) {
  Node *previous = NULL;
  Node *current = list->head;
  while (current != NULL) {
    Node *next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }
  list->head = previous;
}

void listClear(SinglyLinkedList *list) {
  while (list->head != NULL) {
    Node *next = list->head->next;
    free(list->head);
    list->head = next;
  }
  list->size = 0;
}

void listPrint(const SinglyLinkedList *list) {
  for (const Node *node = list->head; node != NULL; node = node->next)
    printf("%d%s", node->value, node->next ? " -> " : "\n");
}

int main(void) {
  SinglyLinkedList list;
  listInit(&list);
  listPushFront(&list, 30);
  listPushFront(&list, 20);
  listPushFront(&list, 10);
  listInsertAfter(list.head->next, 25);
  printf("List: ");
  listPrint(&list);
  listReverse(&list);
  printf("Reversed: ");
  listPrint(&list);
  printf("Contains 20: %s\n", listFind(&list, 20) ? "yes" : "no");
  listRemoveFirst(&list, 25);
  listClear(&list);
  return 0;
}


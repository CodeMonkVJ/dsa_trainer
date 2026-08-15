#include <bits/stdc++.h>
using namespace std;
typedef struct Node { int value; struct Node* prev; struct Node* next; } Node;
typedef struct { Node* head; Node* tail; size_t size; } DList;
void dlInit(DList* list) { list->head = list->tail = nullptr; list->size = 0; }
void dlClear(DList*) {}
bool dlPushFront(DList*, int) { return false; }
bool dlPushBack(DList*, int) { return false; }
bool dlInsertAt(DList*, size_t, int) { return false; }
bool dlPopFront(DList*, int*) { return false; }
bool dlPopBack(DList*, int*) { return false; }
bool dlEraseAt(DList*, size_t, int*) { return false; }
Node* dlFind(DList*, int) { return nullptr; }
int dlAt(DList*, size_t) { return -123123; }

#include <bits/stdc++.h>
using namespace std;
typedef struct SNode { int value; struct SNode* next; } SNode;
typedef struct { SNode* top; size_t size; } Stack;
void stackInit(Stack* stack) { stack->top = nullptr; stack->size = 0; }
void stackClear(Stack*) {}
bool stackPush(Stack*, int) { return false; }
bool stackPop(Stack*, int*) { return false; }
bool stackPeek(Stack*, int*) { return false; }
bool stackIsEmpty(Stack*) { return true; }

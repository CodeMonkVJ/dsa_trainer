#include <bits/stdc++.h>
using namespace std;
typedef struct { int* data; size_t size; size_t cap; bool isMinHeap; } PQueue;
bool pqInit(PQueue*, size_t, bool) { return false; }
void pqClear(PQueue*) {}
bool pqPush(PQueue*, int) { return false; }
bool pqPop(PQueue*, int*) { return false; }
bool pqPeek(PQueue*, int*) { return false; }
bool pqIsEmpty(PQueue*) { return true; }

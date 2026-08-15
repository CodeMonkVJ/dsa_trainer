#include <bits/stdc++.h>
using namespace std;
typedef struct { size_t size; size_t capacity; int* data; } DynamicArray;
void daInit(DynamicArray* arr) { arr->size = 0; arr->capacity = 4; arr->data = (int*)malloc(arr->capacity * sizeof(int)); }
void daFree(DynamicArray* arr) { free(arr->data); arr->data = nullptr; arr->size = 0; arr->capacity = 0; }
void daClear(DynamicArray* arr) { arr->size = 0; }
void daPushBack(DynamicArray*, int) {}
bool daPopBack(DynamicArray*, int*) { return false; }
int daAt(DynamicArray*, size_t) { return -111111; }

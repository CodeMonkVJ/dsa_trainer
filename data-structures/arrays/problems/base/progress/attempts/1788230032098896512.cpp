#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

typedef struct {
  size_t size;
  size_t capacity;
  int *data;
} DynamicArray;

void daInit(DynamicArray *arr) {
  arr->size = 0;
  arr->capacity = 4;
  arr->data = (int *)malloc(arr->capacity * sizeof(int));
}

void daFree(DynamicArray *arr) {
  free(arr->data);
  arr->data = nullptr;
  arr->size = 0;
  arr->capacity = 0;
}

void daClear(DynamicArray *arr) { arr->size = 0; }

void daPushBack(DynamicArray *arr, int x) {
  if (arr->size == arr->capacity) {
    int *newData = (int *)realloc(arr->data, sizeof(int) * arr->capacity * 2);
    if (newData != NULL) {
      arr->data = newData;
      arr->capacity = arr->capacity * 2;
      arr->data[arr->size] = x;
      arr->size++;
    }
  } else {
    arr->data[arr->size] = x;
    arr->size++;
  }
}

bool daPopBack(DynamicArray *arr, int *x) {
  if (arr->size == 0) {
    return false;
  }
  if (x != nullptr) {
    *x = arr->data[arr->size - 1];
  }
  if (arr->capacity == 4) {
    arr->size--;
  } else {
    arr->size--;
    if (arr->size <= (arr->capacity / 4)) {
      int *tempData =
          (int *)realloc(arr->data, sizeof(int) * (arr->capacity / 2));
      if (tempData != NULL) {
        arr->data = tempData;
        arr->capacity = arr->capacity / 2;
      }
    }
  }
  return true;
}

int daAt(DynamicArray *arr, size_t index) {
  if ((index >= arr->size) || (index < 0)) {
    return -111111;
  } else {
    return arr->data[index];
  }
}

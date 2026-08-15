#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// dynamic array implementation in C

typedef struct {
  size_t size;
  size_t capacity;
  int *data;
} DynamicArray;

void daInit(DynamicArray *arr) {
  arr->capacity = 4;
  arr->data = (int *)malloc(arr->capacity * sizeof(int));
  arr->size = 0;
}

void daFree(DynamicArray *arr) {
  free(arr->data);
  arr->data = NULL;
  arr->size = 0, arr->capacity = 4;
}

void daClear(DynamicArray *arr) { memset(arr->data, 0, arr->size); }

void daPushBack(DynamicArray *arr, int value) {
  if (arr->size + 1 == arr->capacity) {
    int *newArr = (int *)malloc(arr->capacity * 2 * sizeof(int));
    for (int i = 0; i < arr->size; i++) {
      newArr[i] = arr->data[i];
    }
    newArr[arr->size] = value;
    arr->size++;
    arr->capacity *= 2;
    free(arr->data);
    arr->data = NULL;
    arr->data = newArr;
  } else {
    arr->data[arr->size] = value;
    arr->size++;
  }
}

bool daPopBack(DynamicArray *arr, int *outValue) {
  if ((arr->capacity > 4) && (arr->size == (arr->capacity) / 2)) {
    int *newArr = (int *)malloc(arr->capacity / 2 * sizeof(int));
    for (int i = 0; i < arr->size - 1; i++) {
      newArr[i] = arr->data[i];
    }
    if (outValue)
      *outValue = arr->data[arr->size - 1];
    arr->size--;
    arr->capacity /= 2;
    free(arr->data);
    arr->data = NULL;
    arr->data = newArr;
    return true;
  } else if (arr->size > 0) {
    if (outValue)
      *outValue = arr->data[arr->size - 1];
    arr->data[arr->size - 1] = 0;
    arr->size--;
    return true;
  } else {
    return false;
  }
}

int daAt(DynamicArray *arr, size_t index) {
  if ((index >= arr->size) || (index < 0)) {
    return -111111;
  } else {
    return arr->data[index];
  }
}

int main(void) {
  DynamicArray arr;
  daInit(&arr);
  for (int i = 0; i < 100; i++) {
    daPushBack(&arr, i * 10);
  }
  for (int i = 0; i < 50; i++) {
    daPopBack(&arr, NULL);
  }
  printf("size=%zu capacity=%zu\n", arr.size, arr.capacity);
  for (size_t i = 0; i < arr.size; i++) {
    printf("%d ", daAt(&arr, i));
  }
  printf("\n");
  daFree(&arr);
  return 0;
}


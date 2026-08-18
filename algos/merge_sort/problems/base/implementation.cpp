#include <bits/stdc++.h>
using namespace std;

static void merge(int *arr, int left, int mid, int right, int *temp) {
  int i = left;
  int j = mid;
  int k = left;

  while (i < mid && j < right) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }
  while (i < mid)
    temp[k++] = arr[i++];
  while (j < right)
    temp[k++] = arr[j++];

  for (int idx = left; idx < right; ++idx) {
    arr[idx] = temp[idx];
  }
}

static void mergeSortRec(int *arr, int left, int right, int *temp) {
  if (right - left <= 1)
    return;
  int mid = left + (right - left) / 2;
  mergeSortRec(arr, left, mid, temp);
  mergeSortRec(arr, mid, right, temp);
  merge(arr, left, mid, right, temp);
}

static void mergeSort(int *arr, int length) {
  if (length <= 1)
    return;
  int *temp = (int *)malloc(sizeof(int) * length);
  if (temp == NULL) {
    fprintf(stderr, "Allocation failed\n");
    exit(1);
  }
  mergeSortRec(arr, 0, length, temp);
  free(temp);
}

int main() {
  int n = 0;
  if (scanf("%d", &n) != 1 || n < 0) {
    fprintf(stderr, "Provide number of elements followed by the values.\n");
    return 1;
  }

  int *data = (int *)malloc(sizeof(int) * n);
  if (data == NULL) {
    fprintf(stderr, "Allocation failed\n");
    return 1;
  }

  for (int i = 0; i < n; ++i) {
    if (scanf("%d", &data[i]) != 1) {
      fprintf(stderr, "Failed to read value %d\n", i);
      free(data);
      return 1;
    }
  }

  mergeSort(data, n);

  for (int i = 0; i < n; ++i) {
    if (i)
      printf(" ");
    printf("%d", data[i]);
  }
  printf("\n");

  free(data);
  return 0;
}

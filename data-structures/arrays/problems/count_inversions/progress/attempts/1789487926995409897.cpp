#include <bits/stdc++.h>
using namespace std;

long long merge(vector<int> &arr, vector<int> &temp, int left, int mid,
                int right) {
  int i = left;
  int j = mid + 1;
  int k = left;

  int count = 0;

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k] = arr[i];
      i++;
    } else {
      temp[k] = arr[j];
      j++;

      count += mid - i + 1;
    }
    k++;
  }

  while (i <= mid) {
    temp[k] = arr[i];
    i++;
    k++;
  }

  while (j <= right) {
    temp[k] = arr[j];
    j++;
    k++;
  }

  for (i = left; i <= right; i++) {
    arr[i] = temp[i];
  }

  return count;
}

long long mergeSort(vector<int> &arr, vector<int> &temp, int left, int right) {
  if (left >= right)
    return 0;

  int mid = left + (right - left) / 2;

  long long count = 0;

  count += mergeSort(arr, temp, left, mid);
  count += mergeSort(arr, temp, mid + 1, right);

  count += merge(arr, temp, left, mid, right);

  return count;
}

long long countInversions(const vector<int> &values) {
  vector<int> arr = values;
  vector<int> temp(values.size());

  return mergeSort(arr, temp, 0, arr.size() - 1);
}

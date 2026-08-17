#include <bits/stdc++.h>
using namespace std;

static long long mergeAndCount(vector<int>& values, vector<int>& buffer, int left, int right) {
  if (right - left <= 1) return 0;
  const int middle = left + (right - left) / 2;
  long long result = mergeAndCount(values, buffer, left, middle);
  result += mergeAndCount(values, buffer, middle, right);

  int i = left;
  int j = middle;
  int k = left;
  while (i < middle && j < right) {
    if (values[i] <= values[j]) {
      buffer[k++] = values[i++];
    } else {
      buffer[k++] = values[j++];
      result += middle - i;
    }
  }
  while (i < middle) buffer[k++] = values[i++];
  while (j < right) buffer[k++] = values[j++];
  copy(buffer.begin() + left, buffer.begin() + right, values.begin() + left);
  return result;
}

long long countInversions(const vector<int>& values) {
  vector<int> work = values;
  vector<int> buffer(values.size());
  return mergeAndCount(work, buffer, 0, static_cast<int>(work.size()));
}

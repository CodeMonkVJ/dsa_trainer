#include <bits/stdc++.h>
using namespace std;

static vector<int> merge(vector<int> left, vector<int> right) {
  vector<int> ans;
  int n = left.size();
  int m = right.size();
  int i = 0, j = 0;
  while (i < n && j < m) {
    if (left[i] < right[j]) {
      ans.push_back(left[i++]);
    } else if (left[i] > right[j]) {
      ans.push_back(right[j++]);
    } else {
      ans.push_back(left[i++]);
      ans.push_back(right[j++]);
    }
  }
  while (i < n) {
    ans.push_back(left[i++]);
  }
  while (j < m) {
    ans.push_back(right[j++]);
  }
  return ans;
}

static vector<int> sort(vector<int> &values) {
  int n = values.size();
  if (n <= 1)
    return values;

  int split = n / 2;
  vector<int> left(values.begin(), values.begin() + split);
  vector<int> right(values.begin() + split, values.end());
  vector<int> sortedLeft = sort(left);
  vector<int> sortedRight = sort(right);
  return merge(sortedLeft, sortedRight);
}

static void mergeSort(vector<int> &values, int length) {
  vector<int> ans = sort(values);
  for (int i = 0; i < length; i++) {
    values[i] = ans[i];
  }
}

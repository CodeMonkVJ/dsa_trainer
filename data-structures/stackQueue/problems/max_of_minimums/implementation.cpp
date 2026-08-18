#include <bits/stdc++.h>
using namespace std;

vector<int> maxOfMinimums(const vector<int>& values) {
  int n = static_cast<int>(values.size());
  if (n == 0) return {};
  vector<int> left(n), right(n), result(n, numeric_limits<int>::min()), stack;
  for (int i = 0; i < n; ++i) {
    while (!stack.empty() && values[stack.back()] >= values[i]) stack.pop_back();
    left[i] = stack.empty() ? -1 : stack.back();
    stack.push_back(i);
  }
  stack.clear();
  for (int i = n - 1; i >= 0; --i) {
    while (!stack.empty() && values[stack.back()] >= values[i]) stack.pop_back();
    right[i] = stack.empty() ? n : stack.back();
    stack.push_back(i);
  }
  for (int i = 0; i < n; ++i) {
    int window = right[i] - left[i] - 1;
    result[window - 1] = max(result[window - 1], values[i]);
  }
  for (int i = n - 2; i >= 0; --i) result[i] = max(result[i], result[i + 1]);
  return result;
}

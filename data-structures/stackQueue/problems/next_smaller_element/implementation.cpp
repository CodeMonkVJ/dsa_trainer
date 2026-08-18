#include <bits/stdc++.h>
using namespace std;

vector<int> nextSmallerElements(const vector<int>& values) {
  vector<int> result(values.size(), -1);
  vector<int> stack;
  for (int i = static_cast<int>(values.size()) - 1; i >= 0; --i) {
    while (!stack.empty() && stack.back() >= values[i]) stack.pop_back();
    if (!stack.empty()) result[i] = stack.back();
    stack.push_back(values[i]);
  }
  return result;
}

int main() {
  for (int value : nextSmallerElements({4, 8, 5, 2, 25})) cout << value << ' ';
  cout << '\n';
  return 0;
}

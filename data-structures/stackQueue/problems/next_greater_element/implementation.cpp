#include <bits/stdc++.h>
using namespace std;

vector<int> nextGreaterElement(const vector<int> &values) {
  vector<int> result(values.size(), -1);
  stack<int> pending;
  for (int i = static_cast<int>(values.size()) - 1; i >= 0; --i) {
    while (!pending.empty() && pending.top() <= values[i]) pending.pop();
    if (!pending.empty()) result[i] = pending.top();
    pending.push(values[i]);
  }
  return result;
}

int main() { return 0; }

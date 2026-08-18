#include <bits/stdc++.h>
using namespace std;

class MinStack {
  vector<pair<int, int>> values;
 public:
  void push(int value) { values.push_back({value, values.empty() ? value : min(value, values.back().second)}); }
  void pop() { values.pop_back(); }
  int top() const { return values.back().first; }
  int getMin() const { return values.back().second; }
  bool empty() const { return values.empty(); }
};

int main() { MinStack values; values.push(3); values.push(1); cout << values.getMin() << '\n'; return 0; }

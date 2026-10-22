#include <bits/stdc++.h>
using namespace std;

class MinStack {
  stack<int> values;
  stack<int> mins;

public:
  void push(int value) {
    values.push(value);
    if (!mins.empty())
      mins.push(min(value, mins.top()));
    else
      mins.push(value);
  }
  void pop() {
    mins.pop();
    values.pop();
  }
  int top() const { return values.top(); }
  int getMin() const { return mins.top(); }
  bool empty() const { return values.empty(); }
};

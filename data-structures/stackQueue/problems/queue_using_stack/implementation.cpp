#include <bits/stdc++.h>
using namespace std;

class MyQueue {
  stack<int> input, output;

  void moveIfNeeded() {
    if (!output.empty()) return;
    while (!input.empty()) {
      output.push(input.top());
      input.pop();
    }
  }

public:
  void push(int value) { input.push(value); }

  int pop() {
    moveIfNeeded();
    if (output.empty()) return -1;
    int value = output.top();
    output.pop();
    return value;
  }

  int peek() {
    moveIfNeeded();
    return output.empty() ? -1 : output.top();
  }

  bool empty() const { return input.empty() && output.empty(); }
};

int main() { return 0; }

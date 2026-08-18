#include <bits/stdc++.h>
using namespace std;

class MyStack {
  queue<int> q;

public:
  void push(int value) {
    q.push(value);
    for (size_t i = 1; i < q.size(); ++i) {
      q.push(q.front());
      q.pop();
    }
  }

  int pop() {
    if (q.empty()) return -1;
    int value = q.front();
    q.pop();
    return value;
  }

  int top() const { return q.empty() ? -1 : q.front(); }
  bool empty() const { return q.empty(); }
};

int main() { return 0; }

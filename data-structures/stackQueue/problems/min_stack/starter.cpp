#include <bits/stdc++.h>
using namespace std;

class MinStack {
public:
  void push(int value) { (void)value; }
  void pop() {}
  int top() const { return 0; }
  int getMin() const { return 0; }
  bool empty() const { return true; }
};

int main() {
  MinStack values;
  values.push(3);
  values.push(1);
  cout << values.getMin() << '\n';
}

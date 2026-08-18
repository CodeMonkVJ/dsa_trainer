#include <bits/stdc++.h>
using namespace std;

static void insertSorted(stack<int>* values, int value) {
  if (values->empty() || values->top() >= value) {
    values->push(value);
    return;
  }
  int top = values->top();
  values->pop();
  insertSorted(values, value);
  values->push(top);
}

void sortStack(stack<int>* values) {
  if (!values || values->empty()) return;
  int top = values->top();
  values->pop();
  sortStack(values);
  insertSorted(values, top);
}

int main() {
  stack<int> values;
  values.push(3); values.push(1); values.push(2);
  sortStack(&values);
  while (!values.empty()) { cout << values.top() << ' '; values.pop(); }
  cout << '\n';
  return 0;
}

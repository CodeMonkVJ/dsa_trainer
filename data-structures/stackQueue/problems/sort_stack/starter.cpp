#include <bits/stdc++.h>
using namespace std;

void sortStack(stack<int> *values) { (void)values; }

int main() {
  stack<int> values;
  values.push(3);
  values.push(1);
  values.push(2);
  sortStack(&values);
  while (!values.empty()) {
    cout << values.top() << ' ';
    values.pop();
  }
  cout << '\n';
}

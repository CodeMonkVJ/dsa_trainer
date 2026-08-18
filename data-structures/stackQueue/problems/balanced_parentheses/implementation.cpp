#include <bits/stdc++.h>
using namespace std;

bool isBalanced(const string &text) {
  stack<char> open;
  for (char c : text) {
    if (c == '(' || c == '{' || c == '[') {
      open.push(c);
    } else if (c == ')' || c == '}' || c == ']') {
      if (open.empty()) return false;
      char expected = c == ')' ? '(' : (c == '}' ? '{' : '[');
      if (open.top() != expected) return false;
      open.pop();
    }
  }
  return open.empty();
}

int main() { return 0; }

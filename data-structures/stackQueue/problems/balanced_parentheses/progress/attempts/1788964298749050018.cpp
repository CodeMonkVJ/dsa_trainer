#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

bool isBalanced(const string &text) {
  stack<char> s;
  unordered_set<char> open = {'(', '{', '['};
  unordered_set<char> close = {')', '}', ']'};
  for (int i = 0; i < text.length(); i++) {
    if (open.find(text[i]) != open.end()) {
      s.push(text[i]);
    } else if (close.find(text[i]) != close.end()) {
      if (s.empty())
        return false;
      char curr = s.top();
      if (curr == '(' && text[i] != ')')
        return false;
      if (curr == '{' && text[i] != '}')
        return false;
      if (curr == '[' && text[i] != ']')
        return false;
      s.pop();
    }
  }

  if (!s.empty())
    return false;

  return true;
}

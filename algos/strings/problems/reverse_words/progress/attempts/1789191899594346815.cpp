#include <bits/stdc++.h>
using namespace std;

static string reverseWords(const string &input) {
  stack<string> s;
  string curr = "";
  int n = input.length();
  int i = 0;
  while (i < n) {
    if (input[i] == ' ') {
      if (curr != "") {
        s.push(curr);
      }
      curr = "";
    } else {
      curr += input[i];
    }
    i++;
  }

  if (curr != "")
    s.push(curr);

  string ans = "";
  while (!s.empty()) {
    ans.append(s.top());
    s.pop();
    if (!s.empty())
      ans += " ";
  }

  return ans;
}

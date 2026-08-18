#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(const string &text, int expected, const char *name) {
  const int actual = longestUniqueSubstring(text);
  ++total;
  cout << "DSA_CASE {\"input\":{\"text\":\"" << text
       << "\"},\"expected\":" << expected << ",\"actual\":" << actual
       << ",\"passed\":" << (actual == expected ? "true" : "false") << "}\n";
  const bool ok = actual == expected;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check("abcabcbb", 3, "finds a window in a repeated string");
  check("bbbbb", 1, "handles all repeated characters");
  check("pwwkew", 3, "moves past the previous duplicate");
  check("", 0, "handles an empty string");
  check("a b!", 4, "treats spaces and punctuation as characters");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

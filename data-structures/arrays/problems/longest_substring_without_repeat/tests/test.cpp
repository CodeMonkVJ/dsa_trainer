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
  check("", 0, "handles an empty string");
  check("a", 1, "handles a single character");

  check("abcdef", 6, "handles all unique characters");
  check("bbbbb", 1, "handles all repeated characters");

  check("abcabcbb", 3, "finds a window in a repeated string");
  check("pwwkew", 3, "moves past the previous duplicate");

  check("abba", 2, "does not move left boundary backwards");
  check("tmmzuxt", 5, "ignores duplicates outside current window");
  check("dvdf", 3, "handles overlapping duplicate history");
  check("anviaj", 5, "handles duplicate after window moves");

  check("aabcdef", 6, "handles duplicate at beginning");
  check("abcdefa", 6, "handles duplicate at end");

  check("a b!", 4, "treats spaces and punctuation as characters");
  check("a a", 2, "handles repeated spaces");
  check("!@#!", 3, "handles punctuation duplicates");

  check("aA", 2, "treats uppercase and lowercase separately");
  check("AaA", 2, "handles case-sensitive duplicates");

  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

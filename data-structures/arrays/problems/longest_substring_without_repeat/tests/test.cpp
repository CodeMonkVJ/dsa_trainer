#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }

int main() {
  check(longestUniqueSubstring("abcabcbb") == 3, "finds a window in a repeated string");
  check(longestUniqueSubstring("bbbbb") == 1, "handles all repeated characters");
  check(longestUniqueSubstring("pwwkew") == 3, "moves past the previous duplicate");
  check(longestUniqueSubstring("") == 0, "handles an empty string");
  check(longestUniqueSubstring("a b!") == 4, "treats spaces and punctuation as characters");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}

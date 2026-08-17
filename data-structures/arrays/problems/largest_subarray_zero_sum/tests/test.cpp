#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }

int main() {
  check(longestZeroSumSubarray({9, -3, 3, -1, 6, -5}) == 5, "finds the longest zero-sum range");
  check(longestZeroSumSubarray({1, 2, -3, 3, -3, 3}) == 5, "keeps the earliest prefix index");
  check(longestZeroSumSubarray({1, 2, 3}) == 0, "returns zero when no range qualifies");
  check(longestZeroSumSubarray({0, 0, 0}) == 3, "handles an all-zero input");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}

#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }

int main() {
  check(longestConsecutive({100, 4, 200, 1, 3, 2}) == 4, "finds a sequence out of order");
  check(longestConsecutive({1, 2, 2, 3, 4, 4}) == 4, "ignores duplicate values");
  check(longestConsecutive({}) == 0, "handles an empty input");
  check(longestConsecutive({-2, -1, 0, 5}) == 3, "handles negative values");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}

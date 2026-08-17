#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(bool ok, const char* name) {
  ++total;
  if (ok) ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check(uniquePaths(3, 7) == 28, "counts a rectangular grid");
  check(uniquePaths(3, 2) == 3, "counts a narrow grid");
  check(uniquePaths(1, 1) == 1, "counts the starting cell");
  check(uniquePaths(0, 5) == 0 && uniquePaths(5, -1) == 0, "rejects invalid dimensions");
  check(uniquePaths(10, 10) == 48620, "handles a larger grid");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}

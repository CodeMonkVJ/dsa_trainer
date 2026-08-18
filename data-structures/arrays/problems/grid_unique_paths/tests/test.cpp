#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(int rows, int columns, long long expected, const char *name) {
  const long long actual = uniquePaths(rows, columns);
  ++total;
  cout << "DSA_CASE {\"input\":{\"rows\":" << rows << ",\"columns\":" << columns
       << "},\"expected\":" << expected << ",\"actual\":" << actual
       << ",\"passed\":" << (actual == expected ? "true" : "false") << "}\n";
  const bool ok = actual == expected;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check(3, 7, 28, "counts a rectangular grid");
  check(3, 2, 3, "counts a narrow grid");
  check(1, 1, 1, "counts the starting cell");
  check(0, 5, 0, "rejects invalid dimensions");
  check(5, -1, 0, "rejects negative dimensions");
  check(10, 10, 48620, "handles a larger grid");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

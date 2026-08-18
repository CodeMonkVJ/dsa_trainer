#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(const vector<int> &values, int expected, const char *name) {
  const int actual = longestZeroSumSubarray(values);
  ++total;
  cout << "DSA_CASE {\"input\":{\"values\":[";
  for (size_t i = 0; i < values.size(); ++i) {
    if (i)
      cout << ',';
    cout << values[i];
  }
  cout << "]},\"expected\":" << expected << ",\"actual\":" << actual
       << ",\"passed\":" << (actual == expected ? "true" : "false") << "}\n";
  const bool ok = actual == expected;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({9, -3, 3, -1, 6, -5}, 5, "finds the longest zero-sum range");
  check({1, 2, -3, 3, -3, 3}, 5, "keeps the earliest prefix index");
  check({1, 2, 3}, 0, "returns zero when no range qualifies");
  check({0, 0, 0}, 3, "handles an all-zero input");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

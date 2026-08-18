#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(const vector<int> &values, int target, int expected,
           const char *name) {
  const int actual = countSubarraysWithXor(values, target);
  ++total;
  cout << "DSA_CASE {\"input\":{\"values\":[";
  for (size_t i = 0; i < values.size(); ++i) {
    if (i)
      cout << ',';
    cout << values[i];
  }
  cout << "],\"target\":" << target << "},\"expected\":" << expected
       << ",\"actual\":" << actual
       << ",\"passed\":" << (actual == expected ? "true" : "false") << "}\n";
  const bool ok = actual == expected;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({4, 2, 2, 6, 4}, 6, 4, "counts the standard example");
  check({5, 5, 5}, 0, 2, "counts multiple equal-prefix ranges");
  check({1, 2, 3}, 7, 0, "returns zero with no matching range");
  check({}, 0, 0, "handles an empty input");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

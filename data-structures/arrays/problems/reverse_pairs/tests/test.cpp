#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(const vector<int> &input, long long expected, const char *name) {
  vector<int> values = input;
  const long long actual = reversePairs(values);
  ++total;
  cout << "DSA_CASE {\"input\":{\"values\":[";
  for (size_t i = 0; i < input.size(); ++i) {
    if (i)
      cout << ',';
    cout << input[i];
  }
  cout << "]},\"expected\":" << expected << ",\"actual\":" << actual
       << ",\"passed\":" << (actual == expected ? "true" : "false") << "}\n";
  const bool ok = actual == expected;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({1, 3, 2, 3, 1}, 2, "counts the standard example");
  check({2, 4, 3, 5, 1}, 3, "counts cross-half pairs");
  check({INT_MAX, INT_MIN, 0}, 2, "uses 64-bit comparisons");
  check({}, 0, "handles an empty array");
  check({1, 2, 3, 4}, 0, "handles no reverse pairs");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

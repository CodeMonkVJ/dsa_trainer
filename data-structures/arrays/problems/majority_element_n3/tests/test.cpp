#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(const vector<int> &values, const vector<int> &expected,
           const char *name) {
  const vector<int> actual = majorityElements(values);
  ++total;
  cout << "DSA_CASE {\"input\":{\"values\":[";
  for (size_t i = 0; i < values.size(); ++i) {
    if (i)
      cout << ',';
    cout << values[i];
  }
  cout << "]},\"expected\":[";
  for (size_t i = 0; i < expected.size(); ++i) {
    if (i)
      cout << ',';
    cout << expected[i];
  }
  cout << "],\"actual\":[";
  for (size_t i = 0; i < actual.size(); ++i) {
    if (i)
      cout << ',';
    cout << actual[i];
  }
  cout << "],\"passed\":" << (actual == expected ? "true" : "false") << "}\n";
  const bool ok = actual == expected;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({3, 2, 3}, {3}, "finds one frequent value");
  check({1, 1, 1, 3, 3, 2, 2, 2}, {1, 2}, "finds two frequent values in order");
  check({1, 2, 3, 4}, {}, "rejects values at the threshold");
  check({}, {}, "handles an empty array");
  check({-2, -2, -2, 5, 5, 7}, {-2}, "handles negative candidates");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

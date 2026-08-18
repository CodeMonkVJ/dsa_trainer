#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(const vector<int> &values, int window, const vector<int> &expected,
           const char *name) {
  const vector<int> actual = slidingWindowMaximum(values, window);
  const bool ok = actual == expected;
  ++total;
  if (ok)
    ++passed;
  cout << "DSA_CASE {\"input\":{\"values\":[";
  for (size_t i = 0; i < values.size(); ++i) {
    if (i)
      cout << ',';
    cout << values[i];
  }
  cout << "],\"window\":" << window << "},\"expected\":[";
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
  cout << "],\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}
void checkInvalid(const vector<int> &values, int window, const char *name) {
  bool actual = false;
  try {
    (void)slidingWindowMaximum(values, window);
  } catch (const invalid_argument &) {
    actual = true;
  }
  const bool ok = actual;
  ++total;
  if (ok)
    ++passed;
  cout << "DSA_CASE {\"input\":{\"values\":[";
  for (size_t i = 0; i < values.size(); ++i) {
    if (i)
      cout << ',';
    cout << values[i];
  }
  cout << "],\"window\":" << window
       << "},\"expected\":true,\"actual\":" << (actual ? "true" : "false")
       << ",\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}
int main() {
  check({1, 3, -1, -3, 5, 3, 6, 7}, 3, {3, 3, 5, 5, 6, 7}, "classic windows");
  check({4, 4, 4}, 2, {4, 4}, "duplicate maxima");
  checkInvalid({1, 2}, 0, "invalid window width");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

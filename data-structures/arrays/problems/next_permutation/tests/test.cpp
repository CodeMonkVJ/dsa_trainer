#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(const vector<int> &input, const vector<int> &expected,
           const char *name) {
  vector<int> actual = input;
  nextPermutation(actual);
  ++total;
  cout << "DSA_CASE {\"input\":{\"values\":[";
  for (size_t i = 0; i < input.size(); ++i) {
    if (i)
      cout << ',';
    cout << input[i];
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
  check({1, 2, 3}, {1, 3, 2}, "advances an increasing permutation");
  check({3, 2, 1}, {1, 2, 3}, "wraps the largest permutation");
  check({1, 1, 5}, {1, 5, 1}, "handles duplicate values");
  check({7}, {7}, "handles a single value");

  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(const vector<vector<int>> &input,
           const vector<vector<int>> &expected, const char *name) {
  vector<vector<int>> actual = input;
  setZeroes(actual);
  ++total;
  cout << "DSA_CASE {\"input\":{\"matrix\":[";
  for (size_t i = 0; i < input.size(); ++i) {
    if (i)
      cout << ',';
    cout << '[';
    for (size_t j = 0; j < input[i].size(); ++j) {
      if (j)
        cout << ',';
      cout << input[i][j];
    }
    cout << ']';
  }
  cout << "]},\"expected\":[";
  for (size_t i = 0; i < expected.size(); ++i) {
    if (i)
      cout << ',';
    cout << '[';
    for (size_t j = 0; j < expected[i].size(); ++j) {
      if (j)
        cout << ',';
      cout << expected[i][j];
    }
    cout << ']';
  }
  cout << "],\"actual\":[";
  for (size_t i = 0; i < actual.size(); ++i) {
    if (i)
      cout << ',';
    cout << '[';
    for (size_t j = 0; j < actual[i].size(); ++j) {
      if (j)
        cout << ',';
      cout << actual[i][j];
    }
    cout << ']';
  }
  cout << "],\"passed\":" << (actual == expected ? "true" : "false") << "}\n";
  const bool ok = actual == expected;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({{1, 1, 1}, {1, 0, 1}, {1, 1, 1}}, {{1, 0, 1}, {0, 0, 0}, {1, 0, 1}},
        "zeros interior row and column");
  check({{0, 1}, {3, 4}}, {{0, 0}, {0, 4}},
        "handles zero in first row and column");
  check({{1, 2, 0, 4}}, {{0, 0, 0, 0}}, "handles a single row");
  check({}, {}, "leaves empty matrix unchanged");

  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

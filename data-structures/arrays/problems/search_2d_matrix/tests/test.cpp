#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(const vector<vector<int>> &matrix, int target, bool expected,
           const char *name) {
  const bool actual = searchMatrix(matrix, target);
  ++total;
  cout << "DSA_CASE {\"input\":{\"matrix\":[";
  for (size_t i = 0; i < matrix.size(); ++i) {
    if (i)
      cout << ',';
    cout << '[';
    for (size_t j = 0; j < matrix[i].size(); ++j) {
      if (j)
        cout << ',';
      cout << matrix[i][j];
    }
    cout << ']';
  }
  cout << "],\"target\":" << target
       << "},\"expected\":" << (expected ? "true" : "false")
       << ",\"actual\":" << (actual ? "true" : "false")
       << ",\"passed\":" << (actual == expected ? "true" : "false") << "}\n";
  const bool ok = actual == expected;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  const vector<vector<int>> matrix{
      {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
  check(matrix, 3, true, "finds a value in the first row");
  check(matrix, 60, true, "finds a value in the last row");
  check(matrix, 13, false, "rejects a missing value");
  check({}, 1, false, "handles an empty matrix");
  check({{}}, 1, false, "handles an empty row");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

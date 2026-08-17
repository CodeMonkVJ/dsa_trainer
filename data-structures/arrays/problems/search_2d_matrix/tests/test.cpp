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
  const vector<vector<int>> matrix{{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
  check(searchMatrix(matrix, 3), "finds a value in the first row");
  check(searchMatrix(matrix, 60), "finds a value in the last row");
  check(!searchMatrix(matrix, 13), "rejects a missing value");
  check(!searchMatrix({}, 1), "handles an empty matrix");
  check(!searchMatrix({{}}, 1), "handles an empty row");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}

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
  vector<vector<int>> matrix{{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
  setZeroes(matrix);
  check(matrix == vector<vector<int>>{{1, 0, 1}, {0, 0, 0}, {1, 0, 1}}, "zeros interior row and column");

  matrix = {{0, 1}, {3, 4}};
  setZeroes(matrix);
  check(matrix == vector<vector<int>>{{0, 0}, {0, 4}}, "handles zero in first row and column");

  matrix = {{1, 2, 0, 4}};
  setZeroes(matrix);
  check(matrix == vector<vector<int>>{{0, 0, 0, 0}}, "handles a single row");

  matrix.clear();
  setZeroes(matrix);
  check(matrix.empty(), "leaves empty matrix unchanged");

  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}

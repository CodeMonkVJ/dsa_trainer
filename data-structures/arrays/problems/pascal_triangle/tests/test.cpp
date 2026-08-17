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
  check(generatePascal(0).empty(), "zero rows are empty");
  check(generatePascal(1) == vector<vector<int>>{{1}}, "generates the first row");
  check(generatePascal(5) == vector<vector<int>>{{1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}, {1, 4, 6, 4, 1}}, "generates five rows");
  check(generatePascal(-2).empty(), "negative row count is empty");

  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}

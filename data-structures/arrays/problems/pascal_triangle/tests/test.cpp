#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(int rows, const vector<vector<int>> &expected, const char *name) {
  const auto actual = generatePascal(rows);
  ++total;
  cout << "DSA_CASE {\"input\":{\"rows\":" << rows << "},\"expected\":";
  cout << "[";
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
  cout << "]";
  cout << ",\"actual\":";
  cout << "[";
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
  cout << "]";
  cout << ",\"passed\":" << (actual == expected ? "true" : "false") << "}\n";
  const bool ok = actual == expected;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check(0, {}, "zero rows are empty");
  check(1, {{1}}, "generates the first row");
  check(5, {{1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}, {1, 4, 6, 4, 1}},
        "generates five rows");
  check(-2, {}, "negative row count is empty");

  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

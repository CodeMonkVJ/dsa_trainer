#include <bits/stdc++.h>
using namespace std;
#include DSA_IMPLEMENTATION

int passed = 0, total = 0;
void check(const vector<vector<int>> &input,
           const vector<vector<int>> &expected, const char *name) {
  const auto actual = mergeIntervals(input);
  ++total;
  auto print = [](const vector<vector<int>> &rows) {
    cout << '[';
    for (size_t i = 0; i < rows.size(); ++i) {
      if (i)
        cout << ',';
      cout << '[';
      for (size_t j = 0; j < rows[i].size(); ++j) {
        if (j)
          cout << ',';
        cout << rows[i][j];
      }
      cout << ']';
    }
    cout << ']';
  };
  cout << "DSA_CASE {\"input\":{\"intervals\":";
  print(input);
  cout << "},\"expected\":";
  print(expected);
  cout << ",\"actual\":";
  print(actual);
  cout << ",\"passed\":" << (actual == expected ? "true" : "false") << "}\n";
  const bool ok = actual == expected;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({{1, 3}, {2, 6}, {8, 10}, {9, 12}}, {{1, 6}, {8, 12}},
        "merges overlapping intervals");
  check({{1, 4}, {4, 5}, {7, 7}}, {{1, 5}, {7, 7}},
        "merges intervals touching at an endpoint");
  check({{-5, -1}, {-4, 3}, {-2, 0}, {10, 12}}, {{-5, 3}, {10, 12}},
        "handles negative and nested intervals");
  check({}, {}, "handles empty input");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

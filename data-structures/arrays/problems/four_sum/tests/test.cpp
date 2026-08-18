#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(const vector<int> &values, long long target,
           const vector<array<int, 4>> &expected, const char *name) {
  const auto actual = fourSum(values, target);
  ++total;
  auto print = [](const vector<array<int, 4>> &rows) {
    cout << '[';
    for (size_t i = 0; i < rows.size(); ++i) {
      if (i)
        cout << ',';
      cout << '[';
      for (size_t j = 0; j < 4; ++j) {
        if (j)
          cout << ',';
        cout << rows[i][j];
      }
      cout << ']';
    }
    cout << ']';
  };
  cout << "DSA_CASE {\"input\":{\"values\":[";
  for (size_t i = 0; i < values.size(); ++i) {
    if (i)
      cout << ',';
    cout << values[i];
  }
  cout << "],\"target\":" << target << "},\"expected\":";
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
  check({1, 0, -1, 0, -2, 2}, 0, {{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}},
        "returns sorted unique quadruplets");
  check({2, 2, 2, 2, 2}, 8, {{2, 2, 2, 2}}, "deduplicates equal values");
  check({1, 2, 3}, 6, {}, "handles too few values");
  check({1000000000, 1000000000, 1000000000, 1000000000}, 4000000000LL,
        {{1000000000, 1000000000, 1000000000, 1000000000}}, "uses wide sums");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

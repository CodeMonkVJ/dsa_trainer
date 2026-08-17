#include <bits/stdc++.h>
using namespace std;
#include DSA_IMPLEMENTATION

int passed = 0, total = 0;
void check(bool ok, const char* name) {
  ++total;
  if (ok) ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check(mergeIntervals({{1, 3}, {2, 6}, {8, 10}, {9, 12}}) ==
            vector<vector<int>>({{1, 6}, {8, 12}}),
        "merges overlapping intervals");
  check(mergeIntervals({{1, 4}, {4, 5}, {7, 7}}) ==
            vector<vector<int>>({{1, 5}, {7, 7}}),
        "merges intervals touching at an endpoint");
  check(mergeIntervals({{-5, -1}, {-4, 3}, {-2, 0}, {10, 12}}) ==
            vector<vector<int>>({{-5, 3}, {10, 12}}),
        "handles negative and nested intervals");
  check(mergeIntervals({}).empty(), "handles empty input");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}

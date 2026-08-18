#include <bits/stdc++.h>
using namespace std;
#include DSA_IMPLEMENTATION

int passed = 0, total = 0;
void check(const vector<int> &values, pair<int, int> expected,
           const char *name) {
  const auto actual = findRepeatingMissing(values);
  ++total;
  cout << "DSA_CASE {\"input\":{\"values\":[";
  for (size_t i = 0; i < values.size(); ++i) {
    if (i)
      cout << ',';
    cout << values[i];
  }
  cout << "]},\"expected\":{\"repeating\":" << expected.first
       << ",\"missing\":" << expected.second
       << "},\"actual\":{\"repeating\":" << actual.first
       << ",\"missing\":" << actual.second
       << "},\"passed\":" << (actual == expected ? "true" : "false") << "}\n";
  const bool ok = actual == expected;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({4, 3, 6, 2, 1, 1}, {1, 5}, "finds repeated one and missing five");
  check({1, 2, 2, 4}, {2, 3}, "handles a repeated middle value");
  check({2, 2}, {2, 1}, "handles the smallest non-empty case");
  check({1, 2, 3, 4, 5, 6, 7, 8, 8, 10}, {8, 9}, "handles a larger range");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

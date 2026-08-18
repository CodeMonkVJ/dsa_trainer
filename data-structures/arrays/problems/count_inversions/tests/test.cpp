#include <bits/stdc++.h>
using namespace std;
#include DSA_IMPLEMENTATION

int passed = 0, total = 0;
void check(const vector<int> &input, long long expected, const char *name) {
  vector<int> values = input;
  const long long actual = countInversions(values);
  ++total;
  cout << "DSA_CASE {\"input\":{\"values\":[";
  for (size_t i = 0; i < input.size(); ++i) {
    if (i)
      cout << ',';
    cout << input[i];
  }
  cout << "]},\"expected\":" << expected << ",\"actual\":" << actual
       << ",\"passed\":" << (actual == expected ? "true" : "false") << "}\n";
  const bool ok = actual == expected;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({5, 3, 2, 4, 1}, 8, "counts inversions");
  check({1, 2, 3, 4}, 0, "returns zero for sorted input");
  check({4, 3, 2, 1}, 6, "counts reverse-order pairs");
  check({2, 2, 1, 1}, 4, "does not count equal values as inversions");
  check({}, 0, "handles empty input");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

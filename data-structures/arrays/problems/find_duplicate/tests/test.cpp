#include <bits/stdc++.h>
using namespace std;
#include DSA_IMPLEMENTATION

int passed = 0, total = 0;
void check(const vector<int> &values, int expected, const char *name) {
  const int actual = findDuplicate(values);
  ++total;
  cout << "DSA_CASE {\"input\":{\"values\":[";
  for (size_t i = 0; i < values.size(); ++i) {
    if (i)
      cout << ',';
    cout << values[i];
  }
  cout << "]},\"expected\":" << expected << ",\"actual\":" << actual
       << ",\"passed\":" << (actual == expected ? "true" : "false") << "}\n";
  const bool ok = actual == expected;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({1, 3, 4, 2, 2}, 2, "finds a duplicate in the middle");
  check({3, 1, 3, 4, 2}, 3, "finds a duplicate at the start of the cycle");
  check({1, 1}, 1, "handles the smallest valid input");
  check({2, 5, 9, 6, 9, 3, 8, 9, 7, 1}, 9,
        "handles a value repeated more than twice");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

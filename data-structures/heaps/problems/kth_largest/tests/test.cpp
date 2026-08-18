#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

string json(const vector<int> &values) {
  ostringstream out;
  out << '[';
  for (size_t i = 0; i < values.size(); ++i) {
    if (i)
      out << ',';
    out << values[i];
  }
  out << ']';
  return out.str();
}

void check(const vector<int> &input, int k, int expected, const char *name) {
  const int actual = findKthLargest(input, k);
  const bool ok = actual == expected;
  ++total;
  if (ok)
    ++passed;
  cout << "DSA_CASE {\"input\":{\"values\":" << json(input) << ",\"k\":" << k
       << "},\"expected\":" << expected << ",\"actual\":" << actual
       << ",\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({3, 2, 1, 5, 6, 4}, 2, 5, "second largest");
  check({3, 2, 3, 1, 2, 4, 5, 5, 6}, 4, 4, "duplicates count");
  check({-7, -2, -9, -2}, 3, -7, "negative values");
  check({42}, 1, 42, "single value");
  check({5, 5, 5, 5}, 4, 5, "all equal");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

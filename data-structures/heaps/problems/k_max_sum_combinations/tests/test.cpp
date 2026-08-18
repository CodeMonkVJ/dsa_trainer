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

void check(const vector<int> &a, const vector<int> &b, int k,
           const vector<int> &expected, const char *name) {
  const vector<int> actual = kMaxSumCombinations(a, b, k);
  const bool ok = actual == expected;
  ++total;
  if (ok)
    ++passed;
  cout << "DSA_CASE {\"input\":{\"a\":" << json(a) << ",\"b\":" << json(b)
       << ",\"k\":" << k << "},\"expected\":" << json(expected)
       << ",\"actual\":" << json(actual)
       << ",\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({1, 4, 2, 3}, {2, 5, 1, 6}, 4, {10, 9, 9, 8}, "basic combinations");
  check({4, 2, 5, 1}, {8, 0, 3, 5}, 3, {13, 12, 10}, "duplicate sums");
  check({-1, -2}, {-3, -4}, 2, {-4, -5}, "negative values");
  check({7}, {6}, 1, {13}, "single pair");
  check({1, 1, 1}, {2, 2, 2}, 3, {3, 3, 3}, "repeated values");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

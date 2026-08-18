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

void check(const vector<int> &input, int k, const vector<int> &expected,
           const char *name) {
  const vector<int> actual = topKFrequent(input, k);
  const bool ok = actual == expected;
  ++total;
  if (ok)
    ++passed;
  cout << "DSA_CASE {\"input\":{\"values\":" << json(input) << ",\"k\":" << k
       << "},\"expected\":" << json(expected) << ",\"actual\":" << json(actual)
       << ",\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({1, 1, 1, 2, 2, 3}, 2, {1, 2}, "basic frequencies");
  check({4, 4, 5, 5, 6}, 2, {4, 5}, "tie breaks by value");
  check({-1, -1, -2, -3, -3, -3, 0}, 3, {-3, -1, -2}, "negative values");
  check({7, 7, 7}, 1, {7}, "single distinct value");
  check({3, 1, 2, 3, 1, 2}, 3, {1, 2, 3}, "k equals distinct count");
  check({8, 8, 8, 1, 1, 2, 2, 2, 3}, 2, {2, 8},
        "evicts low frequency candidate");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

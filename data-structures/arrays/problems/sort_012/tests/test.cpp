#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(const vector<int> &input, const vector<int> &expected,
           const char *name) {
  vector<int> actual = input;
  sort012(actual);
  ++total;
  cout << "DSA_CASE {\"input\":{\"values\":[";
  for (size_t i = 0; i < input.size(); ++i) {
    if (i)
      cout << ',';
    cout << input[i];
  }
  cout << "]},\"expected\":[";
  for (size_t i = 0; i < expected.size(); ++i) {
    if (i)
      cout << ',';
    cout << expected[i];
  }
  cout << "],\"actual\":[";
  for (size_t i = 0; i < actual.size(); ++i) {
    if (i)
      cout << ',';
    cout << actual[i];
  }
  cout << "],\"passed\":" << (actual == expected ? "true" : "false") << "}\n";
  const bool ok = actual == expected;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({2, 0, 2, 1, 1, 0}, {0, 0, 1, 1, 2, 2}, "sorts a mixed array");
  check({2, 2, 2}, {2, 2, 2}, "handles one repeated value");
  check({1, 0, 1}, {0, 1, 1}, "handles a short array");
  check({}, {}, "handles an empty array");

  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

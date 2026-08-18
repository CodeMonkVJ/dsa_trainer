#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(const vector<int> &input, int expected,
           const vector<int> &expectedValues, const char *name) {
  vector<int> actualValues = input;
  const int actual = removeDuplicatesSorted(actualValues);
  actualValues.resize(actual);
  ++total;
  cout << "DSA_CASE {\"input\":{\"values\":[";
  for (size_t i = 0; i < input.size(); ++i) {
    if (i)
      cout << ',';
    cout << input[i];
  }
  cout << "]},\"expected\":{\"count\":" << expected << ",\"values\":[";
  for (size_t i = 0; i < expectedValues.size(); ++i) {
    if (i)
      cout << ',';
    cout << expectedValues[i];
  }
  cout << "]},\"actual\":{\"count\":" << actual << ",\"values\":[";
  for (size_t i = 0; i < actualValues.size(); ++i) {
    if (i)
      cout << ',';
    cout << actualValues[i];
  }
  cout << "]},\"passed\":"
       << (actual == expected && actualValues == expectedValues ? "true"
                                                                : "false")
       << "}\n";
  const bool ok = actual == expected && actualValues == expectedValues;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({0, 0, 1, 1, 1, 2, 2, 3}, 4, {0, 1, 2, 3}, "compacts repeated values");
  check({5, 5, 5}, 1, {5}, "reduces an all-equal input");
  check({-2, 0, 4}, 3, {-2, 0, 4}, "keeps an already unique input");
  check({}, 0, {}, "handles an empty input");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

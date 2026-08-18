#include <bits/stdc++.h>
using namespace std;
#include DSA_IMPLEMENTATION

int passed = 0, total = 0;
void check(const vector<int> &inputFirst, const vector<int> &inputSecond,
           const vector<int> &expectedFirst, const vector<int> &expectedSecond,
           const char *name) {
  vector<int> first = inputFirst, second = inputSecond;
  mergeSortedArrays(first, second);
  ++total;
  cout << "DSA_CASE {\"input\":{\"first\":[";
  for (size_t i = 0; i < inputFirst.size(); ++i) {
    if (i)
      cout << ',';
    cout << inputFirst[i];
  }
  cout << "],\"second\":[";
  for (size_t i = 0; i < inputSecond.size(); ++i) {
    if (i)
      cout << ',';
    cout << inputSecond[i];
  }
  cout << "]},\"expected\":{\"first\":[";
  for (size_t i = 0; i < expectedFirst.size(); ++i) {
    if (i)
      cout << ',';
    cout << expectedFirst[i];
  }
  cout << "],\"second\":[";
  for (size_t i = 0; i < expectedSecond.size(); ++i) {
    if (i)
      cout << ',';
    cout << expectedSecond[i];
  }
  cout << "]},\"actual\":{\"first\":[";
  for (size_t i = 0; i < first.size(); ++i) {
    if (i)
      cout << ',';
    cout << first[i];
  }
  cout << "],\"second\":[";
  for (size_t i = 0; i < second.size(); ++i) {
    if (i)
      cout << ',';
    cout << second[i];
  }
  cout << "]},\"passed\":"
       << (first == expectedFirst && second == expectedSecond ? "true"
                                                              : "false")
       << "}\n";
  const bool ok = first == expectedFirst && second == expectedSecond;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({1, 4, 7, 8, 10}, {2, 3, 9}, {1, 2, 3, 4, 7}, {8, 9, 10},
        "merges unequal lengths");
  check({-3, 0, 0, 8}, {-4, 0, 9, 11}, {-4, -3, 0, 0}, {0, 8, 9, 11},
        "handles duplicates and negative values");
  check({}, {1, 2}, {}, {1, 2}, "handles an empty first vector");
  check({5, 6}, {}, {5, 6}, {}, "handles an empty second vector");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

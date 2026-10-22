#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

void printVector(const vector<int> &v) {
  cout << '[';
  for (size_t i = 0; i < v.size(); ++i) {
    if (i)
      cout << ',';
    cout << v[i];
  }
  cout << ']';
}

void check(const vector<int> &values,
           int window,
           const vector<int> &expected,
           const char *name) {
  const vector<int> actual =
      slidingWindowMaximum(values, window);

  const bool ok = actual == expected;

  ++total;
  if (ok)
    ++passed;

  cout << "DSA_CASE {\"input\":{\"values\":";
  printVector(values);

  cout << ",\"window\":" << window
       << "},\"expected\":";
  printVector(expected);

  cout << ",\"actual\":";
  printVector(actual);

  cout << ",\"passed\":"
       << (ok ? "true" : "false")
       << "}\n";

  cout << (ok ? "PASS " : "FAIL ")
       << name << '\n';
}

int main() {
  check(
      {},
      1,
      {},
      "empty input");

  check(
      {5},
      1,
      {5},
      "single element");

  check(
      {1, 3, -1, -3, 5, 3, 6, 7},
      3,
      {3, 3, 5, 5, 6, 7},
      "classic windows");

  check(
      {4, 4, 4},
      2,
      {4, 4},
      "duplicate maxima");

  check(
      {1, 2, 3, 4},
      1,
      {1, 2, 3, 4},
      "window width one");

  check(
      {1, 2, 3, 4},
      4,
      {4},
      "window covers entire input");

  check(
      {1, 2, 3, 4, 5},
      3,
      {3, 4, 5},
      "strictly increasing");

  check(
      {5, 4, 3, 2, 1},
      3,
      {5, 4, 3},
      "strictly decreasing");

  check(
      {-5, -2, -8, -1, -6},
      2,
      {-2, -2, -1, -1},
      "negative values");

  check(
      {9, 9, 1, 2, 9},
      3,
      {9, 9, 9},
      "duplicate maximum expires");

  check(
      {2, 2, 2, 1, 2, 2},
      3,
      {2, 2, 2, 2},
      "repeated equal maxima");

  check(
      {0, 0, 0, 0},
      2,
      {0, 0, 0},
      "all zeros");

  check(
      {10, 1, 2, 3, 4, 5},
      3,
      {10, 3, 4, 5},
      "old maximum leaves window");

  check(
      {1, 5, 5, 2, 5},
      2,
      {5, 5, 5, 5},
      "equal maxima at different indices");

  check(
      {7, 2, 4},
      3,
      {7},
      "single full-width window");

  check(
      {1, 2},
      0,
      {},
      "zero window rejected");

  check(
      {1, 2},
      -1,
      {},
      "negative window rejected");

  check(
      {1, 2},
      3,
      {},
      "window larger than input rejected");

  check(
      {},
      0,
      {},
      "empty input invalid width");

  check(
      {INT_MIN, INT_MAX, 0},
      2,
      {INT_MAX, INT_MAX},
      "integer extremes");

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}

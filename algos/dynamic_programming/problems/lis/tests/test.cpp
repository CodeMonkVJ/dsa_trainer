#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(const vector<int> &values, int expected, const char *name) {
  ++total;

  int actual = longestIncreasingSubsequence(values);
  bool ok = actual == expected;

  if (ok)
    ++passed;

  cout << (ok ? "PASS " : "FAIL ") << name;

  if (!ok)
    cout << " expected=" << expected << " actual=" << actual;

  cout << '\n';

  cout << "DSA_CASE {\"input\":{\"values\":[";
  for (size_t i = 0; i < values.size(); ++i) {
    if (i)
      cout << ',';
    cout << values[i];
  }

  cout << "]},\"expected\":" << expected
       << ",\"actual\":" << actual
       << ",\"passed\":" << (ok ? "true" : "false")
       << "}\n";
}

int main() {
  // Classic example.
  check(
      {10, 9, 2, 5, 3, 7, 101, 18},
      4,
      "classic LIS");

  // Empty input.
  check(
      {},
      0,
      "empty array");

  // Single element.
  check(
      {7},
      1,
      "single element");

  // Strictly increasing.
  check(
      {1, 2, 3, 4, 5},
      5,
      "already increasing");

  // Strictly decreasing.
  check(
      {5, 4, 3, 2, 1},
      1,
      "decreasing array");

  // All equal: strict increase means only one can be selected.
  check(
      {7, 7, 7, 7},
      1,
      "all equal values");

  // Duplicates should not increase LIS length.
  check(
      {1, 2, 2, 2, 3},
      3,
      "duplicate values");

  // Several possible increasing subsequences.
  check(
      {3, 1, 2, 5, 4, 6},
      4,
      "multiple LIS candidates");

  // Order matters: cannot rearrange values.
  check(
      {4, 1, 3, 2, 5},
      3,
      "subsequence preserves order");

  // Non-contiguous subsequence.
  check(
      {1, 10, 2, 3, 4},
      4,
      "non-contiguous subsequence");

  // Negative values.
  check(
      {-5, -1, -3, 0, 2},
      4,
      "negative values");

  // Mixed negative and positive.
  check(
      {-2, -1, -5, 0, 3, 1, 4},
      5,
      "mixed signed values");

  // Zero values.
  check(
      {0, 0, 1, 2},
      3,
      "zeros and duplicates");

  // Equal value in the middle must not extend the sequence.
  check(
      {1, 2, 2, 3},
      3,
      "strictly increasing with repeated middle value");

  // A smaller tail should replace a larger tail.
  check(
      {2, 5, 3, 7},
      3,
      "tail replacement");

  // Exercises multiple replacements.
  check(
      {10, 4, 7, 2, 5, 8},
      3,
      "multiple tail replacements");

  // Large jump in values doesn't matter.
  check(
      {1, 100, 2, 101, 3, 102},
      4,
      "large value gaps");

  // Interleaved candidates.
  check(
      {10, 22, 9, 33, 21, 50, 41, 60},
      5,
      "interleaved candidates");

  // Extreme integer values.
  check(
      {INT_MIN, -1, 0, INT_MAX},
      4,
      "extreme values increasing");

  // Extreme values in an order that requires skipping.
  check(
      {INT_MAX, INT_MIN, 0},
      2,
      "extreme values mixed");

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
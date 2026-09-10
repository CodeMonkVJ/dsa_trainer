#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(const vector<int> &values, int expected, const char *name) {
  ++total;

  const int actual = longestZeroSumSubarray(values);
  const bool ok = actual == expected;

  if (ok)
    ++passed;

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

  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  // Existing basic case.
  check(
      {9, -3, 3, -1, 6, -5},
      5,
      "finds longest zero-sum range");

  // Entire array sums to zero.
  check(
      {1, 2, -3, 3, -3, 0},
      6,
      "entire array is zero sum");

  // Earliest prefix index must be retained.
  check(
      {1, 2, -3, 3, -3, 3},
      5,
      "keeps earliest prefix index");

  // No qualifying subarray.
  check(
      {1, 2, 3},
      0,
      "no zero-sum subarray");

  // Entire input is zero.
  check(
      {0, 0, 0},
      3,
      "all zeros");

  // Single zero.
  check(
      {0},
      1,
      "single zero");

  // Empty input.
  check(
      {},
      0,
      "empty array");

  // Zero-sum prefix starting at index 0.
  check(
      {1, -1, 5},
      2,
      "zero-sum prefix");

  // Zero-sum suffix.
  check(
      {5, 1, -1},
      2,
      "zero-sum suffix");

  // Zero-sum subarray strictly in the middle.
  check(
      {5, 1, 2, -3, 4},
      3,
      "zero-sum subarray in middle");

  // Negative values.
  check(
      {-1, -2, 3, 0, 5},
      4,
      "negative values");

  // Multiple overlapping zero-sum ranges.
  check(
      {3, -3, 4, -4},
      4,
      "overlapping zero-sum ranges");

  // Repeated prefix sum with a long gap.
  check(
      {2, -1, -1, 3, -3, 1},
      5,
      "repeated prefix sums");

  // Multiple repeated values.
  check(
      {1, -1, 1, -1, 1, -1},
      6,
      "alternating zero-sum values");

  // Only a shorter internal range qualifies.
  check(
      {4, 2, -2, 7},
      2,
      "short internal zero-sum range");

  // Large cancellation.
  check(
      {1000000000, -1000000000},
      2,
      "large cancelling values");

  // Long prefix followed by unrelated values.
  check(
      {1, -1, 2, 3, 4},
      2,
      "zero-sum prefix with trailing values");

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
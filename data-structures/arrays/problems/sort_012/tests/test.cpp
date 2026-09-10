#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(const vector<int> &input,
           const vector<int> &expected,
           const char *name) {
  vector<int> actual = input;
  sort012(actual);

  ++total;

  bool ok = actual == expected;

  if (ok)
    ++passed;

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

  cout << "],\"passed\":" << (ok ? "true" : "false") << "}\n";

  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  // Basic mixed case.
  check(
      {2, 0, 2, 1, 1, 0},
      {0, 0, 1, 1, 2, 2},
      "mixed values");

  // Already sorted.
  check(
      {0, 0, 1, 1, 2, 2},
      {0, 0, 1, 1, 2, 2},
      "already sorted");

  // Reverse sorted.
  check(
      {2, 2, 1, 1, 0, 0},
      {0, 0, 1, 1, 2, 2},
      "reverse sorted");

  // All one value.
  check(
      {2, 2, 2, 2},
      {2, 2, 2, 2},
      "all twos");

  check(
      {1, 1, 1, 1},
      {1, 1, 1, 1},
      "all ones");

  check(
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      "all zeros");

  // Empty and single element.
  check(
      {},
      {},
      "empty array");

  check(
      {0},
      {0},
      "single zero");

  check(
      {1},
      {1},
      "single one");

  check(
      {2},
      {2},
      "single two");

  // Small edge cases.
  check(
      {2, 0},
      {0, 2},
      "two elements");

  check(
      {1, 2},
      {1, 2},
      "two already ordered");

  check(
      {2, 1},
      {1, 2},
      "two reversed");

  // Lots of 0s and 2s: stresses repeated swapping.
  check(
      {2, 2, 2, 0, 0, 0},
      {0, 0, 0, 2, 2, 2},
      "zeros and twos only");

  // Interleaved all three values.
  check(
      {2, 1, 0, 2, 1, 0, 2, 1, 0},
      {0, 0, 0, 1, 1, 1, 2, 2, 2},
      "fully interleaved");

  // Forces 2 to swap with an unprocessed value.
  check(
      {2, 0, 1},
      {0, 1, 2},
      "two swaps with unknown region");

  check(
      {1, 2, 0},
      {0, 1, 2},
      "one of each");

  // Many consecutive zeros/ones/twos.
  check(
      {1, 1, 2, 2, 0, 0, 1, 2, 0},
      {0, 0, 0, 1, 1, 1, 2, 2, 2},
      "multiple regions");

  // Large imbalance between frequencies.
  check(
      {2, 0, 2, 2, 2, 1, 0, 0, 1, 2},
      {0, 0, 0, 1, 1, 2, 2, 2, 2, 2},
      "unequal frequencies");

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}

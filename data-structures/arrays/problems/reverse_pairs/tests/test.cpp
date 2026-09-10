#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

string jsonValues(const vector<int> &values) {
  string s = "[";
  for (size_t i = 0; i < values.size(); ++i) {
    if (i)
      s += ",";
    s += to_string(values[i]);
  }
  return s + "]";
}

void check(const vector<int> &input,
           long long expected,
           const char *name) {
  vector<int> values = input;

  const long long actual = reversePairs(values);

  vector<int> expectedSorted = input;
  sort(expectedSorted.begin(), expectedSorted.end());

  const bool countOk = (actual == expected);
  const bool sortedOk = (values == expectedSorted);
  const bool ok = countOk && sortedOk;

  ++total;
  if (ok)
    ++passed;

  cout << "DSA_CASE {\"input\":{\"values\":"
       << jsonValues(input)
       << "},\"expected\":" << expected
       << ",\"actual\":" << actual
       << ",\"sorted_expected\":" << jsonValues(expectedSorted)
       << ",\"sorted_actual\":" << jsonValues(values)
       << ",\"passed\":" << (ok ? "true" : "false")
       << "}\n";

  cout << (ok ? "PASS " : "FAIL ")
       << name;

  if (!countOk)
    cout << " [wrong count]";

  if (!sortedOk)
    cout << " [array not sorted]";

  cout << '\n';
}

int main() {
  // Standard examples.
  check(
      {1, 3, 2, 3, 1},
      2,
      "standard example");

  check(
      {2, 4, 3, 5, 1},
      3,
      "cross half pairs");

  // Empty input.
  check(
      {},
      0,
      "empty array");

  // Single element.
  check(
      {7},
      0,
      "single element");

  // Already sorted positive values.
  check(
      {1, 2, 3, 4},
      0,
      "sorted positive array");

  // Simple reverse pair.
  //
  // 5 > 2 * 1
  check(
      {5, 1},
      1,
      "single reverse pair");

  // No reverse pair.
  check(
      {1, 5},
      0,
      "two elements no pair");

  // Descending does not mean every pair is a reverse pair.
  check(
      {5, 4, 3, 2, 1},
      4,
      "descending array");

  // Duplicate positive values.
  check(
      {2, 2, 2, 2},
      0,
      "equal positive values");

  // Zeros.
  check(
      {0, 0, 0},
      0,
      "all zeros");

  // Negative values are important.
  //
  // -5 > 2 * -5
  // -5 > -10 -> true
  check(
      {-5, -5},
      1,
      "equal negative values");

  // Mixed negative values.
  check(
      {-5, -2, -6, -1},
      2,
      "mixed negative values");

  // Sorted negative values can still contain reverse pairs.
  check(
      {-5, -4, -3, -2, -1},
      4,
      "sorted negative array");

  // Mixed signs.
  check(
      {4, -1, 2, -3},
      4,
      "mixed positive and negative");

  // Many duplicates.
  check(
      {4, 1, 2, 1, 4, 1},
      4,
      "duplicates");

  // Repeated large-small pattern.
  check(
      {10, 1, 10, 1, 10, 1},
      6,
      "alternating large and small");

  // 64-bit multiplication is required here.
  check(
      {INT_MAX, INT_MIN, 0},
      2,
      "uses 64 bit comparison");

  // Multiple extreme values.
  check(
      {INT_MAX, INT_MAX, INT_MIN, INT_MIN},
      5,
      "multiple integer extremes");

  // Exact boundary must NOT count.
  //
  // 2 > 2 * 1 is false because it is equal.
  check(
      {2, 1},
      0,
      "strict comparison boundary");

  // Just above boundary.
  //
  // 3 > 2 * 1
  check(
      {3, 1},
      1,
      "just above comparison boundary");

  // Several cross-half matches.
  check(
      {8, 4, 2, 1},
      3,
      "multiple cross half matches");

  // Array remains correctly sorted after counting.
  check(
      {9, -2, 7, 1, 0, -5, 3},
      13,
      "larger mixed array");

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
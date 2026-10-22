#include <bits/stdc++.h>
using namespace std;

#include DSA_IMPLEMENTATION

int passed = 0, total = 0;

void check(const vector<int> &input,
           long long expected,
           const char *name) {
  vector<int> values = input;

  const long long actual = countInversions(values);
  const bool unchanged = values == input;
  const bool ok = actual == expected && unchanged;

  ++total;
  if (ok)
    ++passed;

  cout << "DSA_CASE {\"input\":{\"values\":[";

  for (size_t i = 0; i < input.size(); ++i) {
    if (i)
      cout << ',';
    cout << input[i];
  }

  cout << "]},\"expected\":" << expected
       << ",\"actual\":" << actual
       << ",\"input_unchanged\":" << (unchanged ? "true" : "false")
       << ",\"passed\":" << (ok ? "true" : "false")
       << "}\n";

  cout << (ok ? "PASS " : "FAIL ")
       << name << '\n';
}

int main() {
  check(
      {},
      0,
      "empty input");

  check(
      {42},
      0,
      "single element");

  check(
      {1, 2, 3, 4},
      0,
      "sorted input");

  check(
      {4, 3, 2, 1},
      6,
      "reverse order");

  check(
      {5, 3, 2, 4, 1},
      8,
      "mixed inversions");

  check(
      {2, 2, 1, 1},
      4,
      "equal values are not inversions");

  check(
      {7, 7, 7, 7},
      0,
      "all equal");

  check(
      {-1, -2, -3},
      3,
      "negative descending values");

  check(
      {-3, -1, -2, 0},
      1,
      "mixed negative values");

  check(
      {-1, 3, -2, 2, 0},
      5,
      "mixed signs");

  check(
      {8, 4, 2, 6, 1, 5, 3, 7},
      15,
      "longer jumbled array");

  check(
      {1, 3, 2, 4, 5},
      1,
      "single inversion");

  check(
      {2, 1, 3, 4, 5},
      1,
      "single inversion near front");

  check(
      {1, 2, 3, 5, 4},
      1,
      "single inversion near end");

  check(
      {3, 1, 2},
      2,
      "small cross-half inversions");

  check(
      {4, 5, 6, 1, 2, 3},
      9,
      "all inversions across halves");

  check(
      {1, 1, 3, 2, 2},
      2,
      "duplicates with partial inversions");

  check(
      {3, 3, 2, 2, 1, 1},
      12,
      "duplicate groups descending");

  check(
      {INT_MAX, INT_MIN},
      1,
      "integer extremes");

  check(
      {INT_MIN, 0, INT_MAX},
      0,
      "sorted integer extremes");

  check(
      {INT_MAX, 0, INT_MIN},
      3,
      "reverse integer extremes");

  // 6 elements reversed -> 6*5/2 = 15.
  check(
      {6, 5, 4, 3, 2, 1},
      15,
      "larger reverse order");

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
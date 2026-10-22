#include <bits/stdc++.h>
using namespace std;

#include DSA_IMPLEMENTATION

int passed = 0, total = 0;

void check(const vector<int> &values,
           pair<int, int> expected,
           const char *name) {
  const vector<int> original = values;

  const auto actual = findRepeatingMissing(values);

  const bool unchanged = values == original;
  const bool ok = actual == expected && unchanged;

  ++total;
  if (ok)
    ++passed;

  cout << "DSA_CASE {\"input\":{\"values\":[";

  for (size_t i = 0; i < values.size(); ++i) {
    if (i)
      cout << ',';
    cout << values[i];
  }

  cout << "]},\"expected\":{\"repeating\":"
       << expected.first
       << ",\"missing\":"
       << expected.second
       << "},\"actual\":{\"repeating\":"
       << actual.first
       << ",\"missing\":"
       << actual.second
       << "},\"input_unchanged\":"
       << (unchanged ? "true" : "false")
       << ",\"passed\":"
       << (ok ? "true" : "false")
       << "}\n";

  cout << (ok ? "PASS " : "FAIL ")
       << name << '\n';
}

int main() {
  check(
      {4, 3, 6, 2, 1, 1},
      {1, 5},
      "repeating one missing middle-high");

  check(
      {1, 2, 2, 4},
      {2, 3},
      "repeated middle value");

  check(
      {2, 2},
      {2, 1},
      "smallest valid size repeating high");

  check(
      {1, 1},
      {1, 2},
      "smallest valid size repeating low");

  check(
      {2, 3, 4, 5, 5},
      {5, 1},
      "repeating n missing one");

  check(
      {1, 1, 2, 3, 4},
      {1, 5},
      "repeating one missing n");

  check(
      {1, 2, 3, 4, 5, 6, 7, 8, 8, 10},
      {8, 9},
      "larger range");

  check(
      {1, 2, 3, 4, 5, 7, 7},
      {7, 6},
      "duplicate at end");

  check(
      {6, 2, 3, 4, 5, 6},
      {6, 1},
      "missing first value");

  check(
      {1, 2, 3, 4, 5, 5},
      {5, 6},
      "missing last value");

  check(
      {3, 1, 2, 5, 3},
      {3, 4},
      "unsorted classic case");

  check(
      {5, 1, 4, 2, 2},
      {2, 3},
      "unsorted repeated middle");

  check(
      {1, 3, 4, 4, 5},
      {4, 2},
      "missing low value");

  check(
      {1, 2, 3, 3, 5},
      {3, 4},
      "adjacent repeat in sorted input");

  check(
      {4, 2, 1, 4},
      {4, 3},
      "repeat appears far apart");

  check(
      {10, 2, 3, 4, 5, 6, 7, 8, 9, 10},
      {10, 1},
      "larger repeating maximum");

  check(
      {1, 1, 3, 4, 5, 6, 7, 8, 9, 10},
      {1, 2},
      "larger repeating minimum");

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
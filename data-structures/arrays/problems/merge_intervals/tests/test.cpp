#include <bits/stdc++.h>
using namespace std;

#include DSA_IMPLEMENTATION

int passed = 0, total = 0;

void printRows(const vector<vector<int>> &rows) {
  cout << '[';
  for (size_t i = 0; i < rows.size(); ++i) {
    if (i)
      cout << ',';

    cout << '[';
    for (size_t j = 0; j < rows[i].size(); ++j) {
      if (j)
        cout << ',';
      cout << rows[i][j];
    }
    cout << ']';
  }
  cout << ']';
}

void check(const vector<vector<int>> &input,
           const vector<vector<int>> &expected,
           const char *name) {
  const auto actual = mergeIntervals(input);
  const bool ok = actual == expected;

  ++total;
  if (ok)
    ++passed;

  cout << "DSA_CASE {\"input\":{\"intervals\":";
  printRows(input);

  cout << "},\"expected\":";
  printRows(expected);

  cout << ",\"actual\":";
  printRows(actual);

  cout << ",\"passed\":"
       << (ok ? "true" : "false")
       << "}\n";

  cout << (ok ? "PASS " : "FAIL ")
       << name << '\n';
}

int main() {
  check(
      {},
      {},
      "empty input");

  check(
      {{1, 3}},
      {{1, 3}},
      "single interval");

  check(
      {{1, 3}, {2, 6}, {8, 10}, {9, 12}},
      {{1, 6}, {8, 12}},
      "overlapping intervals");

  check(
      {{1, 4}, {4, 5}, {7, 7}},
      {{1, 5}, {7, 7}},
      "touching endpoint merges");

  check(
      {{1, 2}, {2, 3}, {3, 4}, {4, 5}},
      {{1, 5}},
      "chain of touching intervals");

  check(
      {{1, 10}, {2, 3}, {4, 8}, {9, 12}},
      {{1, 12}},
      "large interval absorbs nested and overlapping intervals");

  check(
      {{1, 10}, {2, 3}, {4, 5}, {6, 7}},
      {{1, 10}},
      "fully nested intervals");

  check(
      {{5, 7}, {1, 3}, {2, 6}, {10, 12}},
      {{1, 7}, {10, 12}},
      "unsorted input");

  check(
      {{1, 2}, {5, 6}, {9, 10}},
      {{1, 2}, {5, 6}, {9, 10}},
      "already disjoint");

  check(
      {{9, 10}, {1, 2}, {5, 6}},
      {{1, 2}, {5, 6}, {9, 10}},
      "disjoint unsorted output sorted");

  check(
      {{2, 5}, {2, 5}, {2, 5}},
      {{2, 5}},
      "duplicate intervals");

  check(
      {{1, 5}, {1, 3}, {1, 4}},
      {{1, 5}},
      "same start different ends");

  check(
      {{1, 5}, {2, 5}, {3, 5}},
      {{1, 5}},
      "same end different starts");

  check(
      {{1, 1}, {1, 2}, {2, 2}},
      {{1, 2}},
      "zero length intervals touching");

  check(
      {{1, 1}, {3, 3}, {5, 5}},
      {{1, 1}, {3, 3}, {5, 5}},
      "separate zero length intervals");

  check(
      {{-5, -1}, {-4, 3}, {-2, 0}, {10, 12}},
      {{-5, 3}, {10, 12}},
      "negative and nested intervals");

  check(
      {{-10, -8}, {-8, -5}, {-4, 0}},
      {{-10, -5}, {-4, 0}},
      "negative touching intervals");

  check(
      {{-10, 10}, {-5, 5}, {0, 20}},
      {{-10, 20}},
      "intervals spanning zero");

  check(
      {{1, 2}, {3, 4}, {2, 3}},
      {{1, 4}},
      "bridge interval merges two groups");

  check(
      {{1, 100}, {20, 30}, {40, 50}, {60, 70}},
      {{1, 100}},
      "one interval contains all others");

  check(
      {{INT_MIN, -1}, {-1, 0}, {1, INT_MAX}},
      {{INT_MIN, 0}, {1, INT_MAX}},
      "integer extreme endpoints");

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
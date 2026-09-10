#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

string jsonValues(const vector<int> &values) {
  string result = "[";

  for (size_t i = 0; i < values.size(); ++i) {
    if (i)
      result += ",";
    result += to_string(values[i]);
  }

  return result + "]";
}

void check(const vector<int> &input,
           const vector<int> &expected,
           const char *name) {
  ++total;

  vector<int> values = input;
  mergeSort(values, static_cast<int>(values.size()));

  bool ok = (values == expected);

  if (ok)
    ++passed;

  cout << (ok ? "PASS " : "FAIL ")
       << name
       << " expected=" << jsonValues(expected)
       << " actual=" << jsonValues(values)
       << '\n';

  dsa_test::emit_case(
      jsonValues(input),
      jsonValues(expected),
      jsonValues(values),
      ok);
}

int main() {
  // Mixed values + duplicate + negative.
  check(
      {5, 1, 4, 2, 8, 5, -1},
      {-1, 1, 2, 4, 5, 5, 8},
      "mixed values");

  // Empty input.
  check(
      {},
      {},
      "empty input");

  // Single value.
  check(
      {7},
      {7},
      "single element");

  // Already sorted.
  check(
      {1, 2, 3, 4, 5, 6},
      {1, 2, 3, 4, 5, 6},
      "already sorted");

  // Reverse sorted.
  check(
      {6, 5, 4, 3, 2, 1},
      {1, 2, 3, 4, 5, 6},
      "reverse sorted");

  // Two elements - swapped.
  check(
      {2, 1},
      {1, 2},
      "two elements swapped");

  // Two elements - already sorted.
  check(
      {1, 2},
      {1, 2},
      "two elements sorted");

  // All equal values.
  check(
      {4, 4, 4, 4, 4},
      {4, 4, 4, 4, 4},
      "all equal");

  // Many duplicates.
  check(
      {3, 1, 2, 3, 2, 1, 3, 1},
      {1, 1, 1, 2, 2, 3, 3, 3},
      "many duplicates");

  // All negative.
  check(
      {-5, -1, -10, -3, -7},
      {-10, -7, -5, -3, -1},
      "all negative");

  // Mixed positive, negative, and zero.
  check(
      {0, -10, 5, -3, 8, 0, -1},
      {-10, -3, -1, 0, 0, 5, 8},
      "mixed signs and zero");

  // Odd number of elements.
  check(
      {9, 3, 7, 1, 5},
      {1, 3, 5, 7, 9},
      "odd length");

  // Even number of elements.
  check(
      {8, 2, 6, 4, 7, 1},
      {1, 2, 4, 6, 7, 8},
      "even length");

  // Smallest element at end.
  check(
      {2, 3, 4, 5, 1},
      {1, 2, 3, 4, 5},
      "minimum at end");

  // Largest element at beginning.
  check(
      {100, 1, 2, 3, 4},
      {1, 2, 3, 4, 100},
      "maximum at beginning");

  // Repeated alternating values.
  check(
      {2, 1, 2, 1, 2, 1},
      {1, 1, 1, 2, 2, 2},
      "alternating duplicates");

  // Extreme integer values.
  check(
      {INT_MAX, 0, INT_MIN, -1, 1},
      {INT_MIN, -1, 0, 1, INT_MAX},
      "integer extremes");

  // Larger shuffled input.
  check(
      {12, 5, 19, 1, 7, 14, 3, 18, 2, 10},
      {1, 2, 3, 5, 7, 10, 12, 14, 18, 19},
      "larger shuffled input");

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(bool ok, const char *name) {
  ++total;

  if (ok)
    ++passed;

  cout << (ok ? "PASS " : "FAIL ") << name << '\n';

  string input =
      string("{\"test\":\"") + name + "\"}";

  dsa_test::emit_case(
      input,
      "true",
      ok ? "true" : "false",
      ok);
}

int main() {
  // Basic case.
  check(
      kthLargest({3, 2, 1, 5, 6, 4}, 2) == 5,
      "basic kth largest");

  // Duplicate values count separately.
  check(
      kthLargest({3, 2, 3, 1, 2, 4, 5, 5, 6}, 4) == 4,
      "duplicates count separately");

  // Largest element.
  check(
      kthLargest({3, 1, 7, 2, 5}, 1) == 7,
      "k equals one");

  // Smallest element.
  check(
      kthLargest({3, 1, 7, 2, 5}, 5) == 1,
      "k equals number of elements");

  // Single element.
  check(
      kthLargest({42}, 1) == 42,
      "single element");

  // All values equal.
  check(
      kthLargest({7, 7, 7, 7, 7}, 3) == 7,
      "all equal values");

  // Negative values.
  check(
      kthLargest({-5, -1, -10, -3, -2}, 2) == -2,
      "negative values");

  // Mixed negative and positive.
  check(
      kthLargest({-5, 10, 0, -2, 7, 3}, 3) == 3,
      "mixed signed values");

  // Duplicates around the kth position.
  check(
      kthLargest({9, 9, 8, 8, 7, 7, 6}, 4) == 8,
      "duplicate boundary");

  // Unsorted input.
  check(
      kthLargest({100, 1, 50, 75, 25, 90, 10}, 3) == 75,
      "unsorted input");

  // k = 1 with duplicates.
  check(
      kthLargest({2, 5, 5, 1, 4}, 1) == 5,
      "maximum with duplicates");

  // k = n with duplicates.
  check(
      kthLargest({2, 5, 5, 1, 4}, 5) == 1,
      "minimum with duplicates");

  // Invalid k = 0.
  check(
      kthLargest({1, 2, 3}, 0) == -1,
      "rejects k zero");
  
  // Invalid k greater than size.
  check(
      kthLargest({1, 2, 3}, 4) == -1,
      "rejects k larger than input");
  
  // Empty input.
  check(
      kthLargest({}, 1) == -1,
      "rejects empty input");
  
  // Forces repeated heap eviction.
  check(
      kthLargest({1, 20, 3, 18, 5, 16, 7, 14, 9, 12}, 3) == 16,
      "repeated heap eviction");
  
  // Large duplicates.
  check(
      kthLargest({5, 1, 5, 2, 5, 3, 5, 4}, 4) == 5,
      "many duplicate maximums");

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(const vector<int> &prices,
           int length,
           int expected,
           const char *name) {
  ++total;

  int actual = rodCutting(prices, length);
  bool ok = (actual == expected);

  if (ok)
    ++passed;

  cout << (ok ? "PASS " : "FAIL ")
       << name
       << " expected=" << expected
       << " actual=" << actual
       << '\n';

  dsa_test::emit_case(
      string("{\"test\":\"") + name + "\"}",
      to_string(expected),
      to_string(actual),
      ok);
}

int main() {
  // Classic example.
  check(
      {2, 5, 7, 8, 10},
      5,
      12,
      "classic example");

  // Zero rod length.
  check(
      {2, 5, 7},
      0,
      0,
      "zero rod length");

  // Empty prices.
  check(
      {},
      0,
      0,
      "empty prices zero length");

  // Single available piece length.
  // Only length 1 is priced, so it must be reused.
  check(
      {3},
      5,
      15,
      "reuse single piece length");

  // Best choice is not to cut.
  check(
      {1, 5, 8, 10},
      4,
      10,
      "no cut is best");

  // Repeated smaller pieces beat the direct price.
  //
  // length 4:
  // direct = 7
  // 2 + 2 = 5 + 5 = 10
  check(
      {2, 5, 6, 7},
      4,
      10,
      "repeated smaller pieces");

  // Mixed cut is optimal.
  //
  // length 5:
  // 2 + 3 = 5 + 8 = 13
  check(
      {2, 5, 8, 9, 10},
      5,
      13,
      "mixed cut optimal");

  // Reusing length 2 repeatedly.
  //
  // length 6:
  // 2 + 2 + 2 = 5 + 5 + 5 = 15
  check(
      {1, 5, 7, 8, 9, 10},
      6,
      15,
      "repeat same cut multiple times");

  // Rod length larger than number of price entries.
  //
  // Available:
  // length 1 -> 2
  // length 2 -> 5
  // length 3 -> 7
  //
  // rod length 7:
  // 2 + 2 + 2 + 1 = 5 + 5 + 5 + 2 = 17
  check(
      {2, 5, 7},
      7,
      17,
      "rod longer than price table");

  // All length-1 cuts are optimal.
  check(
      {5, 6, 7, 8},
      4,
      20,
      "all unit cuts optimal");

  // Direct price dramatically better.
  check(
      {1, 2, 3, 100},
      4,
      100,
      "direct whole rod best");

  // Multiple decompositions give the same optimum.
  //
  // length 4:
  // 2 + 2 = 10
  // 1 + 3 = 10
  check(
      {4, 5, 6, 9},
      4,
      16,
      "multiple optimal cuts");

  // Larger test.
  //
  // length 8:
  // classic prices
  // best = 22
  check(
      {1, 5, 8, 9, 10, 17, 17, 20},
      8,
      22,
      "classic length eight");

  // Another reuse-heavy case.
  //
  // length 10:
  // five pieces of length 2 => 5 * 6 = 30
  check(
      {2, 6, 7, 8},
      10,
      30,
      "long rod repeated reuse");

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
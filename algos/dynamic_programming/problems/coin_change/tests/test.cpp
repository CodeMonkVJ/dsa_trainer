#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

void check(const vector<int> &coins,
           int amount,
           int expected,
           const char *name) {
  ++total;

  int actual = coinChange(coins, amount);
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
  // Standard case.
  check(
      {1, 2, 5},
      11,
      3,
      "classic example");

  // Amount zero always needs zero coins.
  check(
      {1, 2, 5},
      0,
      0,
      "zero amount");

  // Impossible target.
  check(
      {2},
      3,
      -1,
      "impossible amount");

  // Empty coin list with positive amount.
  check(
      {},
      7,
      -1,
      "empty coins positive amount");

  // Empty coin list with zero amount.
  check(
      {},
      0,
      0,
      "empty coins zero amount");

  // Single exact coin.
  check(
      {7},
      7,
      1,
      "single exact coin");

  // Reuse same denomination.
  check(
      {3},
      12,
      4,
      "reuse same coin");

  // Coin larger than target.
  check(
      {10},
      3,
      -1,
      "coin larger than target");

  // Mix of usable and unusable denominations.
  check(
      {10, 3, 4},
      6,
      2,
      "ignore larger denomination");

  // Unsorted input.
  check(
      {5, 1, 2},
      11,
      3,
      "unsorted denominations");

  // Duplicate denominations.
  check(
      {1, 2, 2, 5},
      11,
      3,
      "duplicate denominations");

  // Greedy would fail here:
  // 4 + 1 + 1 = 3 coins
  // 3 + 3 = 2 coins
  check(
      {1, 3, 4},
      6,
      2,
      "greedy trap");

  // Another reuse-heavy case.
  check(
      {2, 5},
      10,
      2,
      "two equal large coins");

  // Must use several coins.
  check(
      {2, 3},
      7,
      3,
      "mixed reuse");

  // Impossible because gcd does not divide target.
  check(
      {4, 6},
      5,
      -1,
      "gcd impossible");

  // Larger target.
  check(
      {1, 7, 10},
      14,
      2,
      "larger exact combination");

  // Another classic case.
  check(
      {2, 5, 10, 1},
      27,
      4,
      "classic larger target");

  // Negative amount should be rejected.
  check(
      {1, 2, 5},
      -3,
      -1,
      "negative amount");

  // Previous states may be impossible.
  //
  // dp[1] and dp[3] are impossible,
  // but dp[4] = 2 using 2 + 2.
  check(
      {2},
      4,
      2,
      "skip impossible previous states");

  // Exact large denomination beats smaller combinations.
  check(
      {1, 3, 5, 9},
      9,
      1,
      "exact denomination best");

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
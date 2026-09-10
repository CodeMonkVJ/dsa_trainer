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

  string input = string("{\"test\":\"") + name + "\"}";

  dsa_test::emit_case(
      input,
      "true",
      ok ? "true" : "false",
      ok);
}

int main() {
  // Basic propagation.
  check(
      orangesRotting({
          {2, 1, 1},
          {1, 1, 0},
          {0, 1, 1}
      }) == 4,
      "multi-source spread");

  // Fresh orange that can never be reached.
  check(
      orangesRotting({
          {2, 1, 1},
          {0, 1, 1},
          {1, 0, 1}
      }) == -1,
      "unreachable fresh orange");

  // No fresh oranges.
  check(
      orangesRotting({{0, 2}}) == 0,
      "no fresh oranges");

  // Fresh orange with no rotten source.
  check(
      orangesRotting({{1}}) == -1,
      "fresh without rotten source");

  // Empty grid.
  check(
      orangesRotting({}) == 0,
      "empty grid");

  // Small rectangular grid.
  check(
      orangesRotting({
          {2, 1},
          {1, 1}
      }) == 2,
      "small rectangular grid");

  // Already completely rotten.
  check(
      orangesRotting({
          {2, 2},
          {2, 2}
      }) == 0,
      "all rotten");

  // Single fresh orange next to rotten.
  check(
      orangesRotting({{2, 1}}) == 1,
      "single minute");

  // Single row, long propagation.
  check(
      orangesRotting({{2, 1, 1, 1, 1}}) == 4,
      "single row propagation");

  // Single column, long propagation.
  check(
      orangesRotting({
          {2},
          {1},
          {1},
          {1}
      }) == 3,
      "single column propagation");

  // Multiple rotten sources spreading simultaneously.
  check(
      orangesRotting({
          {2, 1, 1, 2},
          {1, 1, 1, 1},
          {1, 1, 1, 1}
      }) == 3,
      "multiple initial rotten sources");

  // Rotten sources reduce the propagation distance.
  check(
      orangesRotting({
          {1, 1, 2, 1, 1}
      }) == 2,
      "two-sided propagation");

  // Fresh oranges surrounded by empty cells but reachable.
  check(
      orangesRotting({
          {2, 1, 0},
          {0, 1, 0},
          {0, 1, 1}
      }) == 4,
      "propagation around obstacles");

  // Completely fresh grid.
  check(
      orangesRotting({
          {1, 1},
          {1, 1}
      }) == -1,
      "all fresh no source");

  // One isolated fresh orange with an otherwise valid component.
  check(
      orangesRotting({
          {2, 1, 0},
          {0, 0, 0},
          {1, 0, 0}
      }) == -1,
      "valid component plus isolated fresh");

  // Zero cells should never affect propagation.
  check(
      orangesRotting({
          {2, 0, 1},
          {2, 0, 1},
          {2, 0, 1}
      }) == -1,
      "blocked by empty cells");

  // All fresh oranges rot immediately from multiple sources.
  check(
      orangesRotting({
          {2, 1, 2},
          {1, 1, 1},
          {2, 1, 2}
      }) == 2,
      "dense multi-source spread");

  // A longer two-dimensional propagation.
  check(
      orangesRotting({
          {2, 1, 1, 1},
          {0, 0, 1, 0},
          {1, 1, 1, 0},
          {0, 0, 1, 0}
      }) == 6,
      "complex reachable case");

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
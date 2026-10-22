#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

void check(bool ok, const char *name) {
  ++total;
  if (ok)
    ++passed;

  cout << (ok ? "PASS " : "FAIL ") << name << '\n';

  string input = string("{\"test\":\"") + name + "\"}";
  dsa_test::emit_case(
      input,
      ok ? "true" : "false",
      ok ? "true" : "false",
      ok);
}

int main() {
  check(
      largestRectangleArea({}) == 0,
      "empty histogram");

  check(
      largestRectangleArea({7}) == 7,
      "single bar");

  check(
      largestRectangleArea({0}) == 0,
      "single zero bar");

  check(
      largestRectangleArea({2, 1, 5, 6, 2, 3}) == 10,
      "classic mixed bars");

  check(
      largestRectangleArea({2, 4}) == 4,
      "two increasing bars");

  check(
      largestRectangleArea({4, 2}) == 4,
      "two decreasing bars");

  check(
      largestRectangleArea({2, 2, 2, 2}) == 8,
      "all equal bars");

  check(
      largestRectangleArea({1, 2, 3, 4, 5}) == 9,
      "strictly increasing");

  check(
      largestRectangleArea({5, 4, 3, 2, 1}) == 9,
      "strictly decreasing");

  check(
      largestRectangleArea({0, 0, 0, 0}) == 0,
      "all zero bars");

  check(
      largestRectangleArea({2, 0, 2}) == 2,
      "zero splits histogram");

  check(
      largestRectangleArea({2, 1, 2}) == 3,
      "valley allows full width rectangle");

  check(
      largestRectangleArea({1, 3, 2, 1, 2}) == 5,
      "best rectangle spans entire histogram");

  check(
      largestRectangleArea({6, 2, 5, 4, 5, 1, 6}) == 12,
      "classic complex histogram");

  check(
      largestRectangleArea({3, 3, 1, 3, 3}) == 6,
      "equal plateaus separated by valley");

  check(
      largestRectangleArea({1, 1, 1, 10, 1, 1, 1}) == 10,
      "single tall bar beats wide low rectangle");

  check(
      largestRectangleArea({5, 1, 1, 1, 1, 5}) == 6,
      "wide low rectangle beats tall edges");

  check(
      largestRectangleArea({2, 3, 3, 2}) == 8,
      "plateau with lower boundaries");

  check(
      largestRectangleArea({4, 4, 1, 4, 4, 4}) == 12,
      "largest rectangle in suffix plateau");

  check(
      largestRectangleArea({4, 4, 4, 1, 2}) == 12,
      "largest rectangle in prefix plateau");

  check(
      largestRectangleArea({2, 5, 5, 5, 2}) == 15,
      "wide tall middle plateau");

  check(
      largestRectangleArea({100000, 100000}) == 200000,
      "large heights");

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
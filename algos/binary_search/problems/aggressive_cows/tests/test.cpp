#include <iostream>
#include <string>
#include <vector>

#ifndef DSA_IMPLEMENTATION
#define DSA_IMPLEMENTATION "../implementation.cpp"
#endif

#include DSA_IMPLEMENTATION

namespace {

int passed = 0, total = 0;

void check(const std::string &name,
           const std::vector<int> &stalls,
           int cows,
           int expected) {
  ++total;

  const int actual = aggressiveCows(stalls, cows);
  const bool ok = actual == expected;

  std::cout << "DSA_CASE {\"input\":{\"stalls\":[";

  for (std::size_t i = 0; i < stalls.size(); ++i) {
    if (i != 0)
      std::cout << ',';
    std::cout << stalls[i];
  }

  std::cout << "],\"cows\":" << cows
            << "},\"expected\":" << expected
            << ",\"actual\":" << actual
            << ",\"passed\":" << (ok ? "true" : "false")
            << "}\n";

  if (ok) {
    ++passed;
    std::cout << "PASS " << name << '\n';
  } else {
    std::cout << "FAIL " << name
              << ": expected " << expected
              << ", got " << actual << '\n';
  }
}

} // namespace

int main() {
  check(
      "classic",
      {1, 2, 4, 8, 9},
      3,
      3);

  check(
      "unsorted input",
      {10, 1, 2, 7, 5},
      3,
      4);

  check(
      "two cows use extremes",
      {4, 8, 15, 16, 23, 42},
      2,
      38);

  check(
      "every stall occupied",
      {0, 10, 20, 30},
      4,
      10);

  check(
      "two stalls",
      {1, 10},
      2,
      9);

  check(
      "consecutive stalls",
      {1, 2, 3, 4, 5},
      3,
      2);

  check(
      "consecutive stalls all cows",
      {1, 2, 3, 4, 5},
      5,
      1);

  check(
      "duplicate positions",
      {3, 3, 3, 10},
      2,
      7);

  check(
      "all positions equal",
      {5, 5, 5, 5},
      2,
      0);

  check(
      "all equal positions all cows",
      {8, 8, 8},
      3,
      0);

  check(
      "duplicates force zero distance",
      {1, 1, 10},
      3,
      0);

  check(
      "negative positions",
      {-10, -5, 0, 10},
      3,
      10);

  check(
      "all negative positions",
      {-20, -15, -10, -5},
      2,
      15);

  check(
      "crosses zero",
      {-100, -10, 0, 10, 100},
      3,
      100);

  check(
      "large gaps",
      {1, 100, 200, 300},
      3,
      100);

  check(
      "optimal skips many stalls",
      {1, 2, 3, 4, 100},
      3,
      3);

  check(
      "irregular spacing",
      {0, 3, 4, 7, 10, 15},
      3,
      7);

  check(
      "unsorted with negative values",
      {20, -10, 5, 0, 10, -20},
      3,
      20);

  check(
      "wide unsorted range",
      {50, 1, 100, 25, 75},
      3,
      49);

  check(
      "tight cluster plus distant stall",
      {1, 2, 3, 50},
      2,
      49);

  std::cout << "DSA_RESULT {\"passed\":"
            << passed
            << ",\"total\":"
            << total
            << "}\n";

  return passed == total ? 0 : 1;
}
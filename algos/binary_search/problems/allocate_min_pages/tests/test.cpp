#include <iostream>
#include <string>
#include <vector>

#ifndef DSA_IMPLEMENTATION
#define DSA_IMPLEMENTATION "../implementation.cpp"
#endif

#include DSA_IMPLEMENTATION

namespace {

int passed = 0;
int total = 0;

void printPages(const std::vector<int> &pages) {
  std::cout << '[';

  for (std::size_t i = 0; i < pages.size(); ++i) {
    if (i)
      std::cout << ',';

    std::cout << pages[i];
  }

  std::cout << ']';
}

void check(const std::string &name,
           const std::vector<int> &pages,
           int students,
           long long expected) {
  ++total;

  const long long actual =
      allocateMinimumPages(pages, students);

  const bool ok = actual == expected;

  if (ok)
    ++passed;

  std::cout << "DSA_CASE {\"input\":{\"case\":\""
            << name
            << "\",\"pages\":";

  printPages(pages);

  std::cout << ",\"students\":"
            << students
            << "},\"expected\":"
            << expected
            << ",\"actual\":"
            << actual
            << ",\"passed\":"
            << (ok ? "true" : "false")
            << "}\n";

  std::cout << (ok ? "PASS " : "FAIL ")
            << name;

  if (!ok) {
    std::cout << ": expected "
              << expected
              << ", got "
              << actual;
  }

  std::cout << '\n';
}

} // namespace

int main() {
  check(
      "classic two students",
      {12, 34, 67, 90},
      2,
      113);

  check(
      "three students",
      {10, 20, 30, 40},
      3,
      40);

  check(
      "one student gets all books",
      {10, 20, 30},
      1,
      60);

  check(
      "one book per student",
      {5, 17, 100},
      3,
      100);

  check(
      "single book",
      {42},
      1,
      42);

  check(
      "too many students",
      {10, 20},
      3,
      -1);

  check(
      "empty books",
      {},
      1,
      -1);

  check(
      "large pages require long long",
      {1000000000, 1000000000, 1000000000},
      2,
      2000000000LL);

  // Exact boundary:
  // [10,20] | [30]
  check(
      "exact capacity boundary",
      {10, 20, 30},
      2,
      30);

  // Best split:
  // [1,2,3] | [4,5]
  // max = 9
  check(
      "uneven increasing pages",
      {1, 2, 3, 4, 5},
      2,
      9);

  // Best split:
  // [7,2,5] | [10,8]
  // max = 18
  check(
      "greedy grouping matters",
      {7, 2, 5, 10, 8},
      2,
      18);

  check(
      "all equal pages two students",
      {10, 10, 10, 10},
      2,
      20);

  check(
      "all equal pages three students",
      {10, 10, 10, 10, 10},
      3,
      20);

  // Must preserve order.
  // Best:
  // [100] | [1,1,1,1]
  check(
      "large first book",
      {100, 1, 1, 1, 1},
      2,
      100);

  // Best:
  // [1,1,1,1] | [100]
  check(
      "large last book",
      {1, 1, 1, 1, 100},
      2,
      100);

  // Contiguity matters here.
  check(
      "alternating large and small",
      {50, 1, 50, 1, 50},
      2,
      101);

  // 4 students, 5 books.
  // Best:
  // [10] | [20] | [30] | [40,50]
  check(
      "almost one book each",
      {10, 20, 30, 40, 50},
      4,
      50);

  // Best split:
  // [5,10,30] | [20] | [15]
  // max = 45
  check(
      "non obvious optimal split",
      {5, 10, 30, 20, 15},
      3,
      35);

  check(
      "many small books",
      {1, 1, 1, 1, 1, 1, 1, 1},
      3,
      3);

  check(
      "two books two students",
      {8, 9},
      2,
      9);

  check(
      "two books one student",
      {8, 9},
      1,
      17);

  // If zero-page books are valid input.
  check(
      "zero page books",
      {0, 0, 10, 0},
      2,
      10);

  // Large sum beyond int range.
  check(
      "very large total",
      {1500000000, 1500000000, 1500000000, 1500000000},
      2,
      3000000000LL);

  std::cout << "DSA_RESULT {\"passed\":"
            << passed
            << ",\"total\":"
            << total
            << "}\n";

  return passed == total ? 0 : 1;
}
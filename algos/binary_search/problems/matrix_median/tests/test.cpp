#include <iostream>
#include <vector>

#ifndef DSA_IMPLEMENTATION
#define DSA_IMPLEMENTATION "../implementation.cpp"
#endif

#include DSA_IMPLEMENTATION

namespace {
int passed = 0;
int total = 0;

void check(const char *name,
           const std::vector<std::vector<int>> &matrix,
           int expected) {
  ++total;

  const int actual = matrixMedian(matrix);
  const bool ok = actual == expected;

  std::cout << "DSA_CASE {\"input\":{\"matrix\":[";
  for (std::size_t row = 0; row < matrix.size(); ++row) {
    if (row != 0)
      std::cout << ',';

    std::cout << '[';

    for (std::size_t column = 0; column < matrix[row].size(); ++column) {
      if (column != 0)
        std::cout << ',';

      std::cout << matrix[row][column];
    }

    std::cout << ']';
  }

  std::cout << "]},\"expected\":" << expected
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
  check("classic matrix",
        {{1, 3, 5},
         {2, 6, 9},
         {3, 6, 9}},
        5);

  check("single element",
        {{7}},
        7);

  check("single row",
        {{1, 2, 3, 4, 5}},
        3);

  check("single column",
        {{1}, {2}, {3}, {4}, {5}},
        3);

  check("all duplicates",
        {{1, 1, 1},
         {1, 1, 1},
         {1, 1, 1}},
        1);

  check("duplicates around median",
        {{1, 2, 2},
         {2, 2, 3},
         {2, 4, 5}},
        2);

  check("negative values",
        {{-9, -4},
         {-8, -2},
         {-7, -1, 0}},
        -4);

  check("mixed negative and positive",
        {{-10, -3, 1},
         {-8, 0, 2},
         {-4, 5, 9}},
        0);

  check("uneven rows",
        {{1, 10},
         {2},
         {3, 4, 5, 6}},
        4);

  check("contains empty rows",
        {{},
         {1, 2, 3},
         {},
         {4, 5},
         {}},
        3);

  check("rows not globally ordered",
        {{10, 20, 30},
         {1, 5, 8},
         {7, 40, 100}},
        10);

  check("wide value range",
        {{-1000000000},
         {0},
         {1000000000}},
        0);

  check("extreme int values",
        {{INT_MIN},
         {0},
         {INT_MAX}},
        0);

  check("median is global minimum",
        {{1},
         {1},
         {100}},
        1);

  check("median is global maximum",
        {{1},
         {100},
         {100}},
        100);

  check("many repeated boundary values",
        {{1, 1, 1},
         {1, 2, 2},
         {2, 2, 2}},
        2);

  std::cout << "DSA_RESULT {\"passed\":" << passed
            << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
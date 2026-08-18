#include <iostream>
#include <vector>

#ifndef DSA_IMPLEMENTATION
#define DSA_IMPLEMENTATION "../implementation.cpp"
#endif

#include DSA_IMPLEMENTATION

namespace {
int passed = 0;
int total = 0;

void check(const char *name, const std::vector<std::vector<int>> &matrix,
           int expected) {
  ++total;
  const int actual = matrixMedian(matrix);
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
  std::cout << "]},\"expected\":" << expected << ",\"actual\":" << actual
            << ",\"passed\":" << (actual == expected ? "true" : "false")
            << "}\n";
  if (actual == expected) {
    ++passed;
    std::cout << "PASS " << name << '\n';
  } else {
    std::cout << "FAIL " << name << ": expected " << expected << ", got "
              << actual << '\n';
  }
}
} // namespace

int main() {
  check("classic matrix", {{1, 3, 5}, {2, 6, 9}, {3, 6, 9}}, 5);
  check("single element", {{7}}, 7);
  check("single row", {{1, 2, 3, 4, 5}}, 3);
  check("duplicate values", {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}, 1);
  check("negative values", {{-9, -4}, {-8, -2}, {-7, -1, 0}}, -4);
  check("uneven rows", {{1, 10}, {2}, {3, 4, 5, 6}}, 4);
  check("wide value range", {{-1000000000}, {0}, {1000000000}}, 0);
  check("empty matrix", {}, 0);
  check("even element count", {{1, 2}, {3, 4}}, 0);
  std::cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
            << "}\n";
  return passed == total ? 0 : 1;
}

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#ifndef DSA_IMPLEMENTATION
#define DSA_IMPLEMENTATION "../implementation.cpp"
#endif
#include DSA_IMPLEMENTATION

namespace {
int passed = 0, total = 0;
void check(const std::string &name, const std::vector<int> &a,
           const std::vector<int> &b, double expected) {
  ++total;
  const double actual = findMedianSortedArrays(a, b);
  std::cout << "DSA_CASE {\"input\":{\"a\":[";
  for (std::size_t i = 0; i < a.size(); ++i) {
    if (i)
      std::cout << ',';
    std::cout << a[i];
  }
  std::cout << "],\"b\":[";
  for (std::size_t i = 0; i < b.size(); ++i) {
    if (i)
      std::cout << ',';
    std::cout << b[i];
  }
  std::cout << "]},\"expected\":" << expected << ",\"actual\":" << actual
            << ",\"passed\":"
            << (std::abs(actual - expected) < 1e-9 ? "true" : "false") << "}\n";
  if (std::abs(actual - expected) < 1e-9) {
    ++passed;
    std::cout << "PASS " << name << '\n';
  } else
    std::cout << "FAIL " << name << ": expected " << expected << ", got "
              << actual << '\n';
}
} // namespace
int main() {
  check("single element first", {1}, {}, 1.0);
  check("single element second", {}, {2}, 2.0);
  
  check("odd lengths", {1, 3}, {2}, 2.0);
  check("even lengths", {1, 2}, {3, 4}, 2.5);
  
  check("empty first even", {}, {1, 2, 3, 4}, 2.5);
  check("empty first odd", {}, {1, 2, 3}, 2.0);
  check("empty second", {-5}, {}, -5.0);
  
  check("first entirely smaller", {1, 2, 3}, {10, 11, 12}, 6.5);
  check("second entirely smaller", {10, 11, 12}, {1, 2, 3}, 6.5);
  
  check("very uneven sizes",
        {5},
        {1, 2, 3, 4, 6, 7, 8, 9},
        5.0);
  
  check("uneven partition",
        {1, 4, 7, 10},
        {2, 3, 8, 9, 11},
        7.0);
  
  check("duplicates", {1, 1, 1}, {1, 1}, 1.0);
  check("duplicates around median", {1, 2, 2}, {2, 2, 3}, 2.0);
  
  check("negative values",
        {-10, -5},
        {-8, -2, 0},
        -5.0);
  
  check("negative even median",
        {-10, -8},
        {-6, -4},
        -7.0);
  
  check("mixed sign", {-5, -1}, {0, 3, 8}, 0.0);
  
  check("large values",
        {1000000000},
        {1000000000},
        1000000000.0);
  
  check("int max overflow guard",
        {INT_MAX},
        {INT_MAX},
        static_cast<double>(INT_MAX));
  
  check("int min overflow guard",
        {INT_MIN},
        {INT_MIN},
        static_cast<double>(INT_MIN));
  std::cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
            << "}\n";
  return passed == total ? 0 : 1;
}

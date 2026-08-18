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
           const std::vector<int> &b, int k, int expected) {
  ++total;
  const int actual = kthElement(a, b, k);
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
  std::cout << "],\"k\":" << k << "},\"expected\":" << expected
            << ",\"actual\":" << actual
            << ",\"passed\":" << (actual == expected ? "true" : "false")
            << "}\n";
  if (actual == expected) {
    ++passed;
    std::cout << "PASS " << name << '\n';
  } else
    std::cout << "FAIL " << name << ": expected " << expected << ", got "
              << actual << '\n';
}
} // namespace
int main() {
  check("first", {2, 3, 6, 7, 9}, {1, 4, 8, 10}, 1, 1);
  check("last", {2, 3, 6, 7, 9}, {1, 4, 8, 10}, 9, 10);
  check("middle", {2, 3, 6, 7, 9}, {1, 4, 8, 10}, 5, 6);
  check("empty first", {}, {1, 5, 9}, 2, 5);
  check("empty second", {-4, 0, 8}, {}, 1, -4);
  check("duplicates", {1, 1, 2}, {1, 2, 2}, 4, 2);
  check("negative", {-10, -5, 0}, {-8, -3}, 2, -8);
  check("uneven sizes", {1}, {2, 3, 4, 5, 6, 7}, 6, 6);
  std::cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
            << "}\n";
  return passed == total ? 0 : 1;
}

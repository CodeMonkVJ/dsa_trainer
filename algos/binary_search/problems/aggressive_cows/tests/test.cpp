#include <iostream>
#include <string>
#include <vector>
#ifndef DSA_IMPLEMENTATION
#define DSA_IMPLEMENTATION "../implementation.cpp"
#endif
#include DSA_IMPLEMENTATION

namespace {
int passed = 0, total = 0;
void check(const std::string &name, const std::vector<int> &stalls, int cows,
           int expected) {
  ++total;
  const int actual = aggressiveCows(stalls, cows);
  std::cout << "DSA_CASE {\"input\":{\"stalls\":[";
  for (std::size_t i = 0; i < stalls.size(); ++i) {
    if (i != 0)
      std::cout << ',';
    std::cout << stalls[i];
  }
  std::cout << "],\"cows\":" << cows << "},\"expected\":" << expected
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
  check("classic", {1, 2, 4, 8, 9}, 3, 3);
  check("unsorted", {10, 1, 2, 7, 5}, 3, 4);
  check("two cows", {4, 8, 15, 16, 23, 42}, 2, 38);
  check("every stall", {0, 10, 20, 30}, 4, 10);
  check("one cow", {5, 100, 200}, 1, 0);
  check("duplicate positions", {3, 3, 3, 10}, 2, 7);
  check("negative positions", {-10, -5, 0, 10}, 3, 10);
  std::cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
            << "}\n";
  return passed == total ? 0 : 1;
}

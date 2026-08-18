#include <iostream>
#include <string>
#include <vector>
#ifndef DSA_IMPLEMENTATION
#define DSA_IMPLEMENTATION "../implementation.cpp"
#endif
#include DSA_IMPLEMENTATION

namespace {
int passed = 0, total = 0;
void check(const std::string &name, const std::vector<int> &pages, int students,
           long long expected) {
  ++total;
  const long long actual = allocateMinimumPages(pages, students);
  std::cout << "DSA_CASE {\"input\":{\"pages\":[";
  for (std::size_t i = 0; i < pages.size(); ++i) {
    if (i)
      std::cout << ',';
    std::cout << pages[i];
  }
  std::cout << "],\"students\":" << students << "},\"expected\":" << expected
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
  check("classic two students", {12, 34, 67, 90}, 2, 113);
  check("three students", {10, 20, 30, 40}, 3, 40);
  check("one student", {10, 20, 30}, 1, 60);
  check("one book each", {5, 17, 100}, 3, 100);
  check("too many students", {10, 20}, 3, -1);
  check("empty books", {}, 1, -1);
  check("large pages", {1000000000, 1000000000, 1000000000}, 2, 2000000000LL);
  check("single book", {42}, 1, 42);
  std::cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
            << "}\n";
  return passed == total ? 0 : 1;
}

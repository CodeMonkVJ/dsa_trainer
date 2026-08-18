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

void check(const std::string &name, const std::vector<int> &values, int target,
           int expected) {
  ++total;
  const int actual = searchRotatedArray(values, target);
  std::cout << "DSA_CASE {\"input\":{\"values\":[";
  for (std::size_t i = 0; i < values.size(); ++i) {
    if (i != 0)
      std::cout << ',';
    std::cout << values[i];
  }
  std::cout << "],\"target\":" << target << "},\"expected\":" << expected
            << ",\"actual\":" << actual
            << ",\"passed\":" << (actual == expected ? "true" : "false")
            << "}\n";
  if (actual == expected) {
    ++passed;
    std::cout << "PASS " << name << '\n';
    return;
  }
  std::cout << "FAIL " << name << ": expected " << expected << ", got "
            << actual << '\n';
}

} // namespace

int main() {
  check("empty", {}, 3, -1);
  check("singleton present", {5}, 5, 0);
  check("singleton absent", {5}, 2, -1);
  check("not rotated present", {1, 3, 5, 7, 9}, 7, 3);
  check("not rotated absent", {1, 3, 5, 7, 9}, 4, -1);
  check("middle of rotation", {4, 5, 6, 7, 0, 1, 2}, 0, 4);
  check("left side of rotation", {4, 5, 6, 7, 0, 1, 2}, 6, 2);
  check("right side of rotation", {4, 5, 6, 7, 0, 1, 2}, 2, 6);
  check("first index after rotation", {6, 7, 0, 1, 2, 4, 5}, 6, 0);
  check("last index", {6, 7, 0, 1, 2, 4, 5}, 5, 6);
  check("absent between values", {6, 7, 0, 1, 2, 4, 5}, 3, -1);
  check("negative values", {-2, 0, 3, 8, -7, -5, -4}, -5, 5);
  check("two values rotated", {2, 1}, 1, 1);

  std::cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
            << "}\n";
  return passed == total ? 0 : 1;
}

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

void check(const std::string &name, const std::vector<int> &values,
           int expected) {
  ++total;
  const int actual = singleNonDuplicate(values);
  std::cout << "DSA_CASE {\"input\":{\"values\":[";
  for (std::size_t i = 0; i < values.size(); ++i) {
    if (i)
      std::cout << ',';
    std::cout << values[i];
  }
  std::cout << "]},\"expected\":" << expected << ",\"actual\":" << actual
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
check("singleton", {7}, 7);

check("small unique beginning", {1, 2, 2}, 1);
check("small unique end", {1, 1, 2}, 2);

check("unique at beginning", {1, 2, 2, 3, 3}, 1);
check("unique in middle", {1, 1, 2, 3, 3, 4, 4}, 2);
check("unique at end", {1, 1, 2, 2, 9}, 9);

check("negative unique", {-8, -8, -3, 0, 0, 4, 4}, -3);
check("all negative", {-10, -10, -7, -7, -3}, -3);

check("contains zero", {-2, -2, 0, 4, 4}, 0);

check("large gaps", {100, 100, 1000, 1000, 1000000}, 1000000);

check("long paired prefix",
      {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 42},
      42);

check("long paired suffix",
      {-9, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11},
      -9);

check("unique near beginning",
      {1, 1, 2, 3, 3, 4, 4, 5, 5},
      2);

check("unique near end",
      {1, 1, 2, 2, 3, 3, 4, 5, 5},
      4);
  std::cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
            << "}\n";
  return passed == total ? 0 : 1;
}

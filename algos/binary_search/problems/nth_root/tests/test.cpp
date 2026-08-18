#include <cstdint>
#include <iostream>

#ifndef DSA_IMPLEMENTATION
#define DSA_IMPLEMENTATION "../implementation.cpp"
#endif

#include DSA_IMPLEMENTATION

namespace {
int passed = 0;
int total = 0;

void check(const char *name, int exponent, long long value, int expected) {
  ++total;
  const int actual = nthRoot(exponent, value);
  std::cout << "DSA_CASE {\"input\":{\"exponent\":" << exponent
            << ",\"value\":" << value << "},\"expected\":" << expected
            << ",\"actual\":" << actual
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
  check("square root", 2, 16, 4);
  check("cube root", 3, 27, 3);
  check("non-perfect square", 2, 15, -1);
  check("non-perfect cube", 3, 28, -1);
  check("first power", 5, 1, 1);
  check("first root", 1, 123456789, 123456789);
  check("large exact root", 10, 1024, 2);
  check("large non-perfect power", 10, 1025, -1);
  check("invalid exponent", 0, 16, -1);
  check("invalid target", 2, 0, -1);
  check("large exact square", 2, 2147395600, 46340);
  check("large non-perfect square", 2, 2147395600LL - 1, -1);
  std::cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
            << "}\n";
  return passed == total ? 0 : 1;
}

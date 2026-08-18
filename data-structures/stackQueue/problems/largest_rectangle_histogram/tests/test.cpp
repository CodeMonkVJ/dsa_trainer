#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char *name) {
  ++total;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << std::endl;
  std::string input = std::string("{\"test\":\"") + name + "\"}";
  dsa_test::emit_case(input, ok ? "true" : "false", ok ? "true" : "false", ok);
}
int main() {
  check(largestRectangleArea({}) == 0, "empty histogram");
  check(largestRectangleArea({2, 1, 5, 6, 2, 3}) == 10, "mixed bars");
  check(largestRectangleArea({2, 4}) == 4, "short histogram");
  check(largestRectangleArea({2, 2, 2, 2}) == 8, "equal bars");
  check(largestRectangleArea({1, 2, 3, 4, 5}) == 9, "increasing bars");
  check(largestRectangleArea({5, 4, 3, 2, 1}) == 9, "decreasing bars");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

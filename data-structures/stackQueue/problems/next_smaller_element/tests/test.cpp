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
  check(nextSmallerElements({4, 8, 5, 2, 25}) == vector<int>({2, 5, 2, -1, -1}),
        "finds next smaller values");
  check(nextSmallerElements({5, 5, 5}) == vector<int>({-1, -1, -1}),
        "requires strictly smaller values");
  check(nextSmallerElements({-1, -3, 0, -2}) == vector<int>({-3, -1, -2, -1}),
        "handles negatives");
  check(nextSmallerElements({}).empty(), "handles empty input");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

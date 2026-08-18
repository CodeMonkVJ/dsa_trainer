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
  check(nextGreaterElement({}).empty(), "empty array");
  check(nextGreaterElement({2, 1, 2, 4, 3}) == vector<int>({4, 2, 4, -1, -1}),
        "standard case");
  check(nextGreaterElement({5, 5, 5}) == vector<int>({-1, -1, -1}),
        "duplicates require strictly greater");
  check(nextGreaterElement({1, 3, 2, 4}) == vector<int>({3, 4, 4, -1}),
        "interleaved values");
  check(nextGreaterElement({-3, -2, -5, -1}) == vector<int>({-2, -1, -1, -1}),
        "negative values");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

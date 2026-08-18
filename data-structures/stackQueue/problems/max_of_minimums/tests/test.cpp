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
  check(maxOfMinimums({}).empty(), "empty input");
  check(maxOfMinimums({10, 20, 30, 50, 10, 70, 30}) ==
            vector<int>({70, 30, 20, 10, 10, 10, 10}),
        "standard example");
  check(maxOfMinimums({1, 2, 3, 4}) == vector<int>({4, 3, 2, 1}),
        "increasing values");
  check(maxOfMinimums({5, 5, 5}) == vector<int>({5, 5, 5}), "equal values");
  check(maxOfMinimums({-1, -2, -3}) == vector<int>({-1, -2, -3}),
        "negative values");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

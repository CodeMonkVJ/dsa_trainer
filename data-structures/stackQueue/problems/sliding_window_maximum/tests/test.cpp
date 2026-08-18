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
  check(maxSlidingWindow({}, 1).empty(), "empty input");
  check(maxSlidingWindow({1, 3, -1, -3, 5, 3, 6, 7}, 3) ==
            vector<int>({3, 3, 5, 5, 6, 7}),
        "mixed values");
  check(maxSlidingWindow({1, 2, 3}, 1) == vector<int>({1, 2, 3}), "window one");
  check(maxSlidingWindow({4, 4, 4}, 3) == vector<int>({4}), "duplicate values");
  check(maxSlidingWindow({1, 2}, 0).empty() &&
            maxSlidingWindow({1, 2}, 3).empty(),
        "invalid windows");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

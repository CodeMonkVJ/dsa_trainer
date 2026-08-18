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
  check(findCelebrity({}) == -1, "empty party");
  check(findCelebrity({{0}}) == 0, "single person");
  check(findCelebrity({{0, 1, 0}, {0, 0, 0}, {1, 1, 0}}) == 1,
        "find celebrity");
  check(findCelebrity({{0, 1}, {1, 0}}) == -1, "mutual acquaintances");
  check(findCelebrity({{0, 1, 0}, {0, 0, 1}, {0, 0, 0}}) == -1, "no celebrity");
  check(findCelebrity(
            {{0, 0, 0, 0}, {1, 0, 1, 0}, {1, 0, 0, 1}, {1, 1, 1, 0}}) == 0,
        "larger party");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

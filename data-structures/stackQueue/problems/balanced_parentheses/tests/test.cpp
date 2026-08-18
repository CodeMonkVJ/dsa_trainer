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
  check(isBalanced(""), "empty string");
  check(isBalanced("([]{})") && isBalanced("a + (b * [c - {d}])"),
        "valid nesting");
  check(!isBalanced("([)]") && !isBalanced("((}"), "mismatched nesting");
  check(!isBalanced(")(") && !isBalanced("{"), "unmatched brackets");
  check(isBalanced("letters only"), "ignore non-brackets");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

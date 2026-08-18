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
  MinStack s;
  check(s.empty(), "starts empty");
  s.push(3);
  s.push(1);
  s.push(2);
  s.push(1);
  check(s.top() == 1 && s.getMin() == 1, "tracks top and duplicate minimum");
  s.pop();
  check(s.getMin() == 1, "retains earlier minimum");
  s.pop();
  check(s.top() == 1 && s.getMin() == 1, "restores previous top");
  s.pop();
  check(s.getMin() == 3, "restores larger minimum");
  s.pop();
  check(s.empty(), "becomes empty after pops");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

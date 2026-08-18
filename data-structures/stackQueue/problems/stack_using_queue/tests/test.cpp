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
  MyStack s;
  check(s.empty() && s.top() == -1 && s.pop() == -1, "empty stack");
  s.push(1);
  s.push(2);
  s.push(3);
  check(!s.empty() && s.top() == 3, "top is newest value");
  check(s.pop() == 3 && s.pop() == 2 && s.pop() == 1, "LIFO order");
  check(s.empty() && s.pop() == -1, "empty after removals");
  for (int i = 0; i < 100; ++i)
    s.push(i);
  bool ordered = true;
  for (int i = 99; i >= 0; --i)
    ordered = ordered && s.pop() == i;
  check(ordered && s.empty(), "many values");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

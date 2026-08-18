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
vector<int> drain(stack<int> values) {
  vector<int> out;
  while (!values.empty()) {
    out.push_back(values.top());
    values.pop();
  }
  return out;
}
int main() {
  stack<int> s;
  s.push(3);
  s.push(1);
  s.push(2);
  sortStack(&s);
  check(drain(s) == vector<int>({1, 2, 3}),
        "sorts mixed values ascending from top");
  s = stack<int>();
  s.push(2);
  s.push(2);
  s.push(-1);
  sortStack(&s);
  check(drain(s) == vector<int>({-1, 2, 2}),
        "handles duplicates and negatives");
  sortStack(nullptr);
  check(true, "ignores null stack");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

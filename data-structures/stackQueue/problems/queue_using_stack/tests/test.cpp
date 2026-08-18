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
  MyQueue q;
  check(q.empty() && q.peek() == -1 && q.pop() == -1, "empty queue");
  q.push(1);
  q.push(2);
  q.push(3);
  check(!q.empty() && q.peek() == 1, "peek is oldest value");
  check(q.pop() == 1 && q.pop() == 2, "FIFO order");
  q.push(4);
  q.push(5);
  check(q.pop() == 3 && q.pop() == 4 && q.pop() == 5, "interleaved operations");
  check(q.empty() && q.pop() == -1, "empty after removals");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

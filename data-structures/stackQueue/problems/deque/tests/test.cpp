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
  Deque deque;
  deque.pushBack(20);
  deque.pushFront(10);
  deque.pushBack(30);
  int value = 0;
  check(deque.size() == 3, "push at both ends");
  check(deque.popFront(value) && value == 10, "pop front");
  check(deque.popBack(value) && value == 30, "pop back");
  check(deque.popFront(value) && value == 20 && deque.empty(),
        "last element and empty state");
  check(!deque.popBack(value), "empty pop");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

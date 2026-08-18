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
  Stack stack;
  stackInit(&stack);
  int value = 0;
  check(stackIsEmpty(&stack) && !stackPeek(&stack, &value), "empty stack");
  stackPush(&stack, 10);
  stackPush(&stack, 20);
  stackPush(&stack, 30);
  check(stack.size == 3 && stackPeek(&stack, &value) && value == 30,
        "push and peek");
  check(stackPop(&stack, &value) && value == 30, "LIFO pop");
  stackClear(&stack);
  check(stack.size == 0 && stack.top == nullptr, "clear resets top");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

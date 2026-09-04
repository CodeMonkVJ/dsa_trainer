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
  
  check(stackIsEmpty(&stack) &&
            stack.size == 0 &&
            stack.top == nullptr &&
            !stackPeek(&stack, &value) &&
            !stackPop(&stack, &value),
        "empty stack");
  
  check(stackPush(&stack, 10) &&
            stackPush(&stack, 20) &&
            stackPush(&stack, 30),
        "push succeeds");
  
  check(stack.size == 3 &&
            !stackIsEmpty(&stack) &&
            stackPeek(&stack, &value) &&
            value == 30,
        "push and peek");
  
  check(stackPop(&stack, &value) &&
            value == 30 &&
            stack.size == 2,
        "first LIFO pop");
  
  check(stackPeek(&stack, &value) &&
            value == 20,
        "peek updates after pop");
  
  check(stackPop(&stack, &value) &&
            value == 20 &&
            stackPop(&stack, &value) &&
            value == 10 &&
            stack.size == 0 &&
            stackIsEmpty(&stack),
        "pops remaining elements in LIFO order");
  
  check(!stackPop(&stack, &value) &&
            !stackPeek(&stack, &value),
        "pop and peek fail on empty stack");
  
  check(stackPush(&stack, 42) &&
            stackPop(&stack, nullptr) &&
            stack.size == 0,
        "pop supports null output pointer");
  
  stackPush(&stack, 1);
  stackPush(&stack, 2);
  stackPush(&stack, 3);
  stackClear(&stack);
  
  check(stack.size == 0 &&
            stack.top == nullptr &&
            stackIsEmpty(&stack),
        "clear resets stack");
  
  check(stackPush(&stack, 99) &&
            stackPeek(&stack, &value) &&
            value == 99,
        "stack remains reusable after clear");
  
  stackClear(&stack);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

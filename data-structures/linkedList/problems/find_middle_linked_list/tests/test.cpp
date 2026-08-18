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
  check(middleNode(nullptr) == nullptr, "handles an empty list");
  ListNode *list = makeList({7});
  check(middleNode(list) == list, "finds the only node");
  freeList(list);

  list = makeList({1, 2, 3, 4, 5});
  check(middleNode(list)->value == 3, "finds the middle of an odd list");
  freeList(list);

  list = makeList({10, 20, 30, 40, 50, 60});
  ListNode *middle = middleNode(list);
  check(middle->value == 40 && middle->next->value == 50,
        "chooses the second middle for an even list");
  freeList(list);

  list = makeList({-3, -3, 0, 99});
  check(middleNode(list)->value == 0,
        "works with duplicate and negative values");
  freeList(list);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

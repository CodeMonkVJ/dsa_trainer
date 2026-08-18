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
vector<int> values(ListNode *head) {
  vector<int> result;
  for (; head != nullptr; head = head->next)
    result.push_back(head->value);
  return result;
}

int main() {
  ListNode *list = makeList({1, 2, 3, 4, 5});
  ListNode *original = list;
  list = reverseList(list);
  check(values(list) == vector<int>({5, 4, 3, 2, 1}),
        "reverses a multi-node list");
  check(list != original && list->next->next->next->next == original,
        "reuses the original nodes");
  freeList(list);

  check(reverseList(nullptr) == nullptr, "handles an empty list");
  list = makeList({42});
  check(reverseList(list) == list && list->next == nullptr,
        "handles a single node");
  freeList(list);

  list = makeList({2, 2, -1, 2});
  list = reverseList(list);
  check(values(list) == vector<int>({2, -1, 2, 2}),
        "preserves duplicate and negative values");
  freeList(list);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

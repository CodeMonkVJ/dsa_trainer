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
ListNode *make(initializer_list<int> values) {
  ListNode *head = nullptr;
  ListNode *tail = nullptr;
  for (int value : values) {
    auto *node = new ListNode(value);
    if (!head)
      head = node;
    else
      tail->next = node;
    tail = node;
  }
  return head;
}
vector<int> values(ListNode *head) {
  vector<int> result;
  for (auto *node = head; node; node = node->next)
    result.push_back(node->val);
  return result;
}
void freeList(ListNode *head) {
  while (head) {
    auto *next = head->next;
    delete head;
    head = next;
  }
}
int main() {
  ListNode *list = removeNthFromEnd(make({1, 2, 3, 4, 5}), 2);
  check(values(list) == vector<int>({1, 2, 3, 5}), "remove middle from end");
  freeList(list);
  list = removeNthFromEnd(make({1}), 1);
  check(values(list).empty(), "remove only node");
  freeList(list);
  list = removeNthFromEnd(make({1, 2, 3}), 3);
  check(values(list) == vector<int>({2, 3}), "remove head");
  freeList(list);
  list = make({1, 2, 3});
  ListNode *unchanged = removeNthFromEnd(list, 0);
  check(unchanged == list && values(list) == vector<int>({1, 2, 3}),
        "reject nonpositive n");
  unchanged = removeNthFromEnd(list, 4);
  check(unchanged == list && values(list) == vector<int>({1, 2, 3}),
        "reject oversized n");
  freeList(list);
  check(removeNthFromEnd(nullptr, 1) == nullptr, "empty list");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

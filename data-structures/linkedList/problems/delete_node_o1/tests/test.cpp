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
  ListNode *a = new ListNode(4);
  ListNode *b = new ListNode(5);
  ListNode *c = new ListNode(1);
  ListNode *d = new ListNode(9);
  a->next = b;
  b->next = c;
  c->next = d;
  deleteNode(b);
  check(values(a) == vector<int>({4, 1, 9}), "delete middle node");
  freeList(a);
  a = new ListNode(1);
  b = new ListNode(2);
  c = new ListNode(3);
  a->next = b;
  b->next = c;
  deleteNode(a);
  check(values(a) == vector<int>({2, 3}), "delete head through pointer");
  freeList(a);
  a = new ListNode(7);
  check(values(a) == vector<int>({7}), "singleton remains unchanged");
  deleteNode(nullptr);
  check(values(a) == vector<int>({7}), "null pointer is safe");
  freeList(a);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

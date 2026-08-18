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
  ListNode *a = make({2, 4, 3});
  ListNode *b = make({5, 6, 4});
  ListNode *sum = addTwoNumbers(a, b);
  check(values(sum) == vector<int>({7, 0, 8}), "basic addition");
  check(values(a) == vector<int>({2, 4, 3}) &&
            values(b) == vector<int>({5, 6, 4}),
        "inputs unchanged");
  freeList(a);
  freeList(b);
  freeList(sum);
  sum = addTwoNumbers(make({9, 9, 9, 9}), make({1}));
  check(values(sum) == vector<int>({0, 0, 0, 0, 1}), "carry across lengths");
  freeList(sum);
  sum = addTwoNumbers(make({0}), make({0}));
  check(values(sum) == vector<int>({0}), "zero values");
  freeList(sum);
  sum = addTwoNumbers(nullptr, make({7, 1}));
  check(values(sum) == vector<int>({7, 1}), "empty input");
  freeList(sum);
  sum = addTwoNumbers(nullptr, nullptr);
  check(values(sum) == vector<int>({0}), "both inputs empty");
  freeList(sum);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

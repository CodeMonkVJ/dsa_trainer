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
  ListNode *left = makeList({1, 3, 5, 7});
  ListNode *right = makeList({2, 4, 6, 8});
  ListNode *leftHead = left;
  ListNode *rightHead = right;
  ListNode *merged = mergeTwoSortedLists(left, right);
  check(values(merged) == vector<int>({1, 2, 3, 4, 5, 6, 7, 8}),
        "merges two sorted lists");
  check(merged == leftHead && merged->next == rightHead,
        "reuses and relinks input nodes");
  freeList(merged);

  left = makeList({-5, -1, 2, 2});
  right = makeList({-5, 0, 2, 9});
  merged = mergeTwoSortedLists(left, right);
  check(values(merged) == vector<int>({-5, -5, -1, 0, 2, 2, 2, 9}),
        "keeps duplicates and negative values");
  freeList(merged);

  left = makeList({1, 2});
  check(values(mergeTwoSortedLists(left, nullptr)) == vector<int>({1, 2}),
        "handles an empty right list");
  freeList(left);
  right = makeList({3, 4});
  check(values(mergeTwoSortedLists(nullptr, right)) == vector<int>({3, 4}),
        "handles an empty left list");
  freeList(right);
  check(mergeTwoSortedLists(nullptr, nullptr) == nullptr,
        "handles two empty lists");

  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

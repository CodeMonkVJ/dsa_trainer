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
vector<int> values(Node *head, size_t limit = 1000) {
  vector<int> out;
  while (head != nullptr && out.size() < limit) {
    out.push_back(head->value);
    head = head->next;
  }
  return out;
}
Node *makeList(const vector<int> &input, vector<unique_ptr<Node>> &storage) {
  Node *head = nullptr;
  Node *tail = nullptr;
  for (int value : input) {
    storage.push_back(make_unique<Node>(value));
    Node *node = storage.back().get();
    if (head == nullptr)
      head = node;
    else
      tail->next = node;
    tail = node;
  }
  return head;
}

int main() {
  vector<unique_ptr<Node>> s1;
  Node *h1 = makeList({1, 2, 3, 4, 5}, s1);
  check(values(reverseKGroup(h1, 2)) == vector<int>({2, 1, 4, 3, 5}),
        "multiple groups with leftover");
  vector<unique_ptr<Node>> s2;
  Node *h2 = makeList({1, 2, 3, 4, 5, 6}, s2);
  check(values(reverseKGroup(h2, 3)) == vector<int>({3, 2, 1, 6, 5, 4}),
        "exact groups");
  vector<unique_ptr<Node>> s3;
  Node *h3 = makeList({1, 2, 3}, s3);
  check(values(reverseKGroup(h3, 5)) == vector<int>({1, 2, 3}),
        "k larger than list");
  vector<unique_ptr<Node>> s4;
  Node *h4 = makeList({1, 2, 3}, s4);
  check(reverseKGroup(h4, 1) == h4 && values(h4) == vector<int>({1, 2, 3}),
        "k one no-op");
  vector<unique_ptr<Node>> s5;
  Node *h5 = makeList({1, 2, 3}, s5);
  check(reverseKGroup(h5, 0) == h5 && values(h5) == vector<int>({1, 2, 3}),
        "non-positive k no-op");
  check(reverseKGroup(nullptr, 3) == nullptr, "empty list");
  vector<unique_ptr<Node>> s6;
  vector<int> large(101);
  iota(large.begin(), large.end(), 0);
  Node *h6 = makeList(large, s6);
  Node *result = reverseKGroup(h6, 10);
  vector<int> expected;
  for (int start = 0; start < 100; start += 10)
    for (int i = start + 9; i >= start; --i)
      expected.push_back(i);
  expected.push_back(100);
  check(values(result) == expected, "large input and short tail");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

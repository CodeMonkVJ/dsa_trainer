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
  for (ListNode *node = head; node; node = node->next)
    result.push_back(node->val);
  return result;
}

int main() {
  ListNode a(1), b(2), c(3), d(4), e(5);
  a.next = &b;
  b.next = &c;
  c.next = &d;
  d.next = &e;
  check(values(rotateRight(&a, 2)) == vector<int>({4, 5, 1, 2, 3}),
        "rotates right");

  ListNode x(1), y(2), z(3);
  x.next = &y;
  y.next = &z;
  check(values(rotateRight(&x, 8)) == vector<int>({2, 3, 1}),
        "reduces large rotations");

  ListNode one(7);
  check(values(rotateRight(&one, 4)) == vector<int>({7}), "handles one node");
  check(rotateRight(nullptr, 3) == nullptr, "handles empty list");

  ListNode p(1), q(2), r(3);
  p.next = &q;
  q.next = &r;
  check(values(rotateRight(&p, 0)) == vector<int>({1, 2, 3}),
        "zero rotation is unchanged");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

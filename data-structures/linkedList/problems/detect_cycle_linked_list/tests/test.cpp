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
  Node one(1), a(1), b(2), c(3), d(4), e(5), p(1), q(2), r(3);
  check(detectCycle(nullptr) == nullptr, "empty list");
  check(detectCycle(&one) == nullptr, "single node without cycle");
  one.next = &one;
  check(detectCycle(&one) == &one, "self cycle");
  one.next = nullptr;
  a.next = &b;
  b.next = &c;
  c.next = &d;
  d.next = &c;
  check(detectCycle(&a) == &c, "cycle begins in middle");
  p.next = &q;
  q.next = &r;
  r.next = &p;
  check(detectCycle(&p) == &p, "cycle begins at head");
  check(detectCycle(&a) == &c && a.next == &b && b.next == &c && c.next == &d &&
            d.next == &c,
        "cyclic links remain unchanged");
  e.next = nullptr;
  check(detectCycle(&e) == nullptr, "one node acyclic");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

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
  Node shared1(8), shared2(10), a1(1), a2(3), b1(2), b2(4), lone(7);
  shared1.next = &shared2;
  a1.next = &a2;
  a2.next = &shared1;
  b1.next = &b2;
  b2.next = &shared1;
  check(getIntersectionNode(&a1, &b1) == &shared1,
        "intersection by node identity");
  check(getIntersectionNode(&a1, &lone) == nullptr, "disjoint lists");
  check(getIntersectionNode(nullptr, &lone) == nullptr &&
            getIntersectionNode(nullptr, nullptr) == nullptr,
        "empty input");
  check(getIntersectionNode(&shared1, &shared1) == &shared1, "same head");
  Node x1(1), x2(2), x3(3), y1(1), y2(2), y3(3);
  x1.next = &x2;
  x2.next = &x3;
  y1.next = &y2;
  y2.next = &y3;
  check(getIntersectionNode(&x1, &y1) == nullptr,
        "same values are not an intersection");
  check(a1.next == &a2 && a2.next == &shared1 && b1.next == &b2 &&
            b2.next == &shared1,
        "lists remain unchanged");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

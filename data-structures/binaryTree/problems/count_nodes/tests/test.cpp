#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool x, const char *n) {
  ++total;
  if (x)
    ++passed;
  string input = "{\"case\":\"" + string(n) + "\"}";
  dsa_test::emit_case(input, "true", x ? "true" : "false", x);
}
int main() {
  check(countNodes(nullptr) == 0, "empty tree");
  TreeNode a(1), b(2), c(3), d(4), e(5), f(6);
  a.left = &b;
  a.right = &c;
  b.left = &d;
  b.right = &e;
  c.left = &f;
  check(countNodes(&a) == 6, "incomplete last level");
  TreeNode x(1), y(2);
  x.left = &y;
  check(countNodes(&x) == 2, "left-only final node");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

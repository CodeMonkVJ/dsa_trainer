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
  TreeNode a(1), b(2), c(3), d(4), e(5), f(6), g(7);
  a.left = &b;
  a.right = &c;
  b.left = &d;
  b.right = &e;
  c.right = &f;
  f.right = &g;
  check(burnTime(&a, 5) == 5, "burn from leaf");
  check(burnTime(&a, 1) == 3, "burn from root");
  check(burnTime(&a, 99) == -1, "missing target");
  TreeNode x(8);
  check(burnTime(&x, 8) == 0, "single node");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

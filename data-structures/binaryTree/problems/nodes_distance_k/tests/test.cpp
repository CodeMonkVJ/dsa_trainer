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
  TreeNode a(3), b(5), c(1), d(6), e(2), f(0), g(8), h(7), i(4);
  a.left = &b;
  a.right = &c;
  b.left = &d;
  b.right = &e;
  c.left = &f;
  c.right = &g;
  e.left = &h;
  e.right = &i;
  auto x = nodesAtDistanceK(&a, 5, 2);
  sort(x.begin(), x.end());
  check(x == vector<int>({1, 4, 7}), "distance two");
  auto y = nodesAtDistanceK(&a, 3, 0);
  check(y == vector<int>({3}), "target itself");
  check(nodesAtDistanceK(&a, 42, 2).empty(), "missing target");
  check(nodesAtDistanceK(&a, 5, -1).empty(), "negative distance");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

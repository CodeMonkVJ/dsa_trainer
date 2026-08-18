#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  TreeNode a{4, nullptr, nullptr}, b{5, nullptr, nullptr}, l{2, &a, nullptr},
      r{3, nullptr, &b}, root{1, &l, &r};
  auto x = lowestCommonAncestor(&root, 4, 5),
       y = lowestCommonAncestor(&root, 4, 2),
       z = lowestCommonAncestor(&root, 4, 9);
  bool xok = x && *x == 1, yok = y && *y == 2, zok = !z;
  dsa_test::emit_case("{\"tree\":[1,2,3,4,null,null,5],\"p\":4,\"q\":5}", "1",
                      x ? to_string(*x) : "null", xok);
  dsa_test::emit_case("{\"tree\":[1,2,3,4,null,null,5],\"p\":4,\"q\":2}", "2",
                      y ? to_string(*y) : "null", yok);
  dsa_test::emit_case("{\"tree\":[1,2,3,4,null,null,5],\"p\":4,\"q\":9}",
                      "null", z ? to_string(*z) : "null", zok);
  bool ok = xok && yok && zok;
  cout << "DSA_RESULT {\"passed\":" << (xok + yok + zok) << ",\"total\":3}\n";
  return ok ? 0 : 1;
}

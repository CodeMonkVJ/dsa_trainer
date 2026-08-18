#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  TreeNode a(1), b(2), c(3), d(4), e(5), f(6);
  a.left = &b;
  a.right = &c;
  b.left = &d;
  b.right = &e;
  d.left = &f;
  int diameter = treeDiameter(&a), empty = treeDiameter(nullptr);
  bool tree_ok = diameter == 4, empty_ok = empty == 0;
  dsa_test::emit_case("{\"tree\":[1,2,3,4,5,null,null,6]}", "4",
                      to_string(diameter), tree_ok);
  dsa_test::emit_case("{\"tree\":null}", "0", to_string(empty), empty_ok);
  TreeNode g(7);
  int single = treeDiameter(&g);
  bool single_ok = single == 0;
  dsa_test::emit_case("{\"tree\":[7]}", "0", to_string(single), single_ok);
  cout << "DSA_RESULT {\"passed\":" << (tree_ok + empty_ok + single_ok)
       << ",\"total\":3}\n";
  return tree_ok && empty_ok && single_ok ? 0 : 1;
}

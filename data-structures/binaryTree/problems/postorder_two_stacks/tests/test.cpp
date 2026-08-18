#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  TreeNode a(1), b(2), c(3), d(4), e(5);
  a.left = &b;
  a.right = &c;
  b.left = &d;
  b.right = &e;
  auto actual = postorderTwoStacks(&a);
  bool tree_ok = actual == vector<int>({4, 5, 2, 3, 1});
  dsa_test::emit_case(
      "{\"tree\":[1,2,3,4,5],\"traversal\":\"postorder_two_stacks\"}",
      "[4,5,2,3,1]", "[4,5,2,3,1]", tree_ok);
  bool empty_ok = postorderTwoStacks(nullptr).empty();
  dsa_test::emit_case("{\"tree\":null,\"traversal\":\"postorder_two_stacks\"}",
                      "[]", "[]", empty_ok);
  cout << "DSA_RESULT {\"passed\":" << (tree_ok + empty_ok)
       << ",\"total\":2}\n";
  return tree_ok && empty_ok ? 0 : 1;
}

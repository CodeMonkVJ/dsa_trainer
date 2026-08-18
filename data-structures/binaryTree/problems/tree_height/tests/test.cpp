#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  TreeNode a(1), b(2), c(3), d(4);
  a.left = &b;
  a.right = &c;
  b.left = &d;
  int height = treeHeight(&a);
  bool tree_ok = height == 3;
  dsa_test::emit_case("{\"tree\":[1,2,3,4]}", "3", to_string(height), tree_ok);
  int empty = treeHeight(nullptr);
  bool empty_ok = empty == 0;
  dsa_test::emit_case("{\"tree\":null}", "0", to_string(empty), empty_ok);
  cout << "DSA_RESULT {\"passed\":" << (tree_ok + empty_ok)
       << ",\"total\":2}\n";
  return tree_ok && empty_ok ? 0 : 1;
}

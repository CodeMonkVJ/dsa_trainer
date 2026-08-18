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
  string input = "{\"case\":\"" + string(name) + "\"}";
  dsa_test::emit_case(input, "true", ok ? "true" : "false", ok);
}
int main() {
  check(boundaryTraversal(nullptr).empty(), "empty tree");
  TreeNode *r = new TreeNode(1);
  r->left = new TreeNode(2);
  r->right = new TreeNode(3);
  r->left->left = new TreeNode(4);
  r->left->right = new TreeNode(5);
  r->right->left = new TreeNode(6);
  r->right->right = new TreeNode(7);
  check(boundaryTraversal(r) == vector<int>{1, 2, 4, 5, 6, 7, 3},
        "complete tree");
  TreeNode *skew = new TreeNode(1);
  skew->right = new TreeNode(2);
  skew->right->left = new TreeNode(3);
  check(boundaryTraversal(skew) == vector<int>{1, 3, 2},
        "right-skewed boundary");
  TreeNode *one = new TreeNode(9);
  check(boundaryTraversal(one) == vector<int>{9}, "single node");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

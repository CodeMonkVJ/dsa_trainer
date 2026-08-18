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
  TreeNode *a = new TreeNode(-10);
  a->left = new TreeNode(9);
  a->right = new TreeNode(20);
  a->right->left = new TreeNode(15);
  a->right->right = new TreeNode(7);
  check(maxPathSum(a) == 42, "crosses through root");
  TreeNode *b = new TreeNode(-3);
  b->left = new TreeNode(-2);
  b->right = new TreeNode(-1);
  check(maxPathSum(b) == -1, "all negative");
  TreeNode *c = new TreeNode(5);
  c->left = new TreeNode(4);
  c->right = new TreeNode(8);
  c->right->left = new TreeNode(11);
  check(maxPathSum(c) == 28, "best path away from root");
  check(maxPathSum(nullptr) == numeric_limits<int>::min(), "empty tree");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

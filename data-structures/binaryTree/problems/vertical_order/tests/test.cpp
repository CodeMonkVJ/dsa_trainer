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
  check(verticalOrder(nullptr).empty(), "empty tree");
  TreeNode *r = new TreeNode(3);
  r->left = new TreeNode(9);
  r->right = new TreeNode(20);
  r->right->left = new TreeNode(15);
  r->right->right = new TreeNode(7);
  check(verticalOrder(r) == vector<vector<int>>{{9}, {3, 15}, {20}, {7}},
        "standard columns");
  TreeNode *tie = new TreeNode(1);
  tie->left = new TreeNode(2);
  tie->right = new TreeNode(3);
  tie->left->right = new TreeNode(4);
  tie->right->left = new TreeNode(5);
  check(verticalOrder(tie) == vector<vector<int>>{{2}, {1, 4, 5}, {3}},
        "same-column breadth-first order");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

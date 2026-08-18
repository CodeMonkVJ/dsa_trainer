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
  check(zigzagTraversal(nullptr).empty(), "empty tree");
  TreeNode *r = new TreeNode(3);
  r->left = new TreeNode(9);
  r->right = new TreeNode(20);
  r->right->left = new TreeNode(15);
  r->right->right = new TreeNode(7);
  check(zigzagTraversal(r) == vector<vector<int>>{{3}, {20, 9}, {15, 7}},
        "alternating levels");
  TreeNode *single = new TreeNode(1);
  single->right = new TreeNode(2);
  single->right->right = new TreeNode(3);
  check(zigzagTraversal(single) == vector<vector<int>>{{1}, {2}, {3}},
        "skewed tree");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

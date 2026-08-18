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
  TreeNode *r = new TreeNode(1);
  r->left = new TreeNode(2);
  r->right = new TreeNode(3);
  r->left->left = new TreeNode(4);
  r->left->right = new TreeNode(5);
  check(morrisInorder(r) == vector<int>({4, 2, 5, 1, 3}), "inorder");
  check(morrisInorder(nullptr).empty(), "empty tree");
  check(r->left->right->right == nullptr, "threads removed");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

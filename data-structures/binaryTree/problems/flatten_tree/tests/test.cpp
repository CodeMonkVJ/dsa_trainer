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
  r->right = new TreeNode(5);
  r->left->left = new TreeNode(3);
  r->left->right = new TreeNode(4);
  r->right->right = new TreeNode(6);
  flatten(r);
  vector<int> v;
  bool ok = true;
  for (TreeNode *n = r; n; n = n->right) {
    v.push_back(n->val);
    ok = ok && n->left == nullptr;
  }
  check(ok && v == vector<int>({1, 2, 3, 4, 5, 6}), "preorder flatten");
  flatten(nullptr);
  check(true, "empty tree");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

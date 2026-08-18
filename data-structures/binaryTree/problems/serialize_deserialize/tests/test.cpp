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
bool same(TreeNode *a, TreeNode *b) {
  return (!a && !b) || (a && b && a->val == b->val && same(a->left, b->left) &&
                        same(a->right, b->right));
}
int main() {
  TreeNode *r = new TreeNode(1);
  r->left = new TreeNode(-2);
  r->right = new TreeNode(3);
  r->left->right = new TreeNode(4);
  check(same(r, deserialize(serialize(r))), "round trip");
  check(deserialize(serialize(nullptr)) == nullptr, "empty tree");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

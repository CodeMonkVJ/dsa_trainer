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
bool valid(TreeNode *n) {
  if (!n)
    return true;
  if (n->left || n->right) {
    int s = (n->left ? n->left->val : 0) + (n->right ? n->right->val : 0);
    if (n->val != s)
      return false;
  }
  return valid(n->left) && valid(n->right);
}
int main() {
  TreeNode a(10), b(8), c(2), d(3), e(5);
  a.left = &b;
  a.right = &c;
  b.left = &d;
  b.right = &e;
  enforceChildrenSum(&a);
  check(valid(&a), "enforce property");
  check(a.val == 10 && b.val == 8, "preserve larger values");
  TreeNode x(4);
  enforceChildrenSum(&x);
  check(x.val == 4, "leaf unchanged");
  check(enforceChildrenSum(nullptr) == nullptr, "empty tree");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

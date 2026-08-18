#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
static TreeNode *n(int v, TreeNode *l = nullptr, TreeNode *r = nullptr) {
  auto *x = new TreeNode(v);
  x->left = l;
  x->right = r;
  return x;
}
static void del(TreeNode *r) {
  if (!r)
    return;
  del(r->left);
  del(r->right);
  delete r;
}
static bool pairIs(pair<TreeNode *, TreeNode *> p, int pre, int succ) {
  return (p.first ? p.first->val : -1) == pre &&
         (p.second ? p.second->val : -1) == succ;
}
int main() {
  int passed = 0, total = 0;
  auto check = [&](bool ok) {
    ++total;
    passed += ok;
    cout << "DSA_CASE {\"input\":{\"case\":" << total
         << "},\"expected\":true,\"actual\":" << (ok ? "true" : "false")
         << ",\"passed\":" << (ok ? "true" : "false") << "}\n";
  };
  TreeNode *root = n(8, n(4, n(2), n(6, n(5), n(7))), n(12, n(10), n(14)));
  check(pairIs(inorderSuccessorPredecessor(root, 6), 5, 7));
  check(pairIs(inorderSuccessorPredecessor(root, 8), 7, 10));
  check(pairIs(inorderSuccessorPredecessor(root, 1), -1, 2));
  check(pairIs(inorderSuccessorPredecessor(root, 13), 12, 14));
  check(pairIs(inorderSuccessorPredecessor(root, 14), 12, -1));
  check(pairIs(inorderSuccessorPredecessor(nullptr, 3), -1, -1));
  del(root);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed != total;
}

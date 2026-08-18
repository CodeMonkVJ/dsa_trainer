#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
static TreeNode *node(int v, TreeNode *l = nullptr, TreeNode *r = nullptr) {
  auto *n = new TreeNode(v);
  n->left = l;
  n->right = r;
  return n;
}
static void destroy(TreeNode *r) {
  if (!r)
    return;
  destroy(r->left);
  destroy(r->right);
  delete r;
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
  TreeNode *root =
      node(5, node(3, node(2), node(4)), node(7, node(6), node(8)));
  check(findTarget(root, 9));
  check(findTarget(root, 10));
  check(!findTarget(root, 20));
  check(!findTarget(root, 4));
  destroy(root);
  root = node(5);
  check(!findTarget(root, 10));
  destroy(root);
  check(!findTarget(nullptr, 0));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed != total;
}

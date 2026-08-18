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
int main() {
  int passed = 0, total = 0;
  auto check = [&](bool ok) {
    ++total;
    passed += ok;
    cout << "DSA_CASE {\"input\":{\"case\":" << total
         << "},\"expected\":true,\"actual\":" << (ok ? "true" : "false")
         << ",\"passed\":" << (ok ? "true" : "false") << "}\n";
  };
  TreeNode *root = n(6, n(2, n(0), n(4, n(3), n(5))), n(8, n(7), n(9)));
  check(lcaBST(root, 2, 8) == root);
  check(lcaBST(root, 3, 5)->val == 4);
  check(lcaBST(root, 0, 5)->val == 2);
  check(lcaBST(root, 7, 9)->val == 8);
  check(lcaBST(root, 3, 42) == nullptr);
  check(lcaBST(nullptr, 1, 2) == nullptr);
  del(root);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed != total;
}

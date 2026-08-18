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
  TreeNode *root = n(8, n(4, n(2), n(6)), n(12, n(10), n(14)));
  check(findCeil(root, 1) == 2);
  check(findCeil(root, 2) == 2);
  check(findCeil(root, 5) == 6);
  check(findCeil(root, 14) == 14);
  check(findCeil(root, 15) == -1);
  check(findCeil(nullptr, 3) == -1);
  del(root);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed != total;
}

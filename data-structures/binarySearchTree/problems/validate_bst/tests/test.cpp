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
  check(isValidBST(nullptr));
  check(isValidBST(n(2, n(1), n(3))));
  TreeNode *bad = n(5, n(1), n(4, n(3), n(6)));
  check(!isValidBST(bad));
  del(bad);
  check(!isValidBST(n(5, n(5), n(7))));
  check(isValidBST(n(INT_MAX, n(INT_MIN), nullptr)));
  check(!isValidBST(n(INT_MIN, nullptr, n(INT_MIN))));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed != total;
}

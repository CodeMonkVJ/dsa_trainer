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
  check(kthSmallestLargest(root, 1) == make_pair(2, 8));
  check(kthSmallestLargest(root, 4) == make_pair(5, 5));
  check(kthSmallestLargest(root, 7) == make_pair(8, 2));
  destroy(root);
  root = node(10);
  check(kthSmallestLargest(root, 1) == make_pair(10, 10));
  destroy(root);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed != total;
}

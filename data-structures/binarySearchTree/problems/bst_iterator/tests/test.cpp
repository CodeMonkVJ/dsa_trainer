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
      node(7, node(3, node(1), node(5)), node(10, nullptr, node(12)));
  BSTIterator it(root);
  vector<int> got;
  while (it.hasNext())
    got.push_back(it.next());
  check(got == vector<int>({1, 3, 5, 7, 10, 12}));
  check(!it.hasNext());
  destroy(root);
  BSTIterator empty(nullptr);
  check(!empty.hasNext());
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed != total;
}

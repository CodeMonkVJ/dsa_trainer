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
  TreeNode *root = node(8, node(3, node(1), node(6, node(4), node(7))),
                        node(10, nullptr, node(14)));
  check(floorBST(root, 0) == -1);
  check(floorBST(root, 1) == 1);
  check(floorBST(root, 5) == 4);
  check(floorBST(root, 8) == 8);
  check(floorBST(root, 13) == 10);
  check(floorBST(root, 20) == 14);
  check(floorBST(nullptr, 5) == -1);
  destroy(root);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed != total;
}

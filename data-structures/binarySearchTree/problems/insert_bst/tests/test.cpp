#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

static vector<int> inorder(TreeNode *r) {
  if (!r)
    return {};
  auto a = inorder(r->left), b = inorder(r->right);
  a.push_back(r->value);
  a.insert(a.end(), b.begin(), b.end());
  return a;
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
  TreeNode *root = nullptr;
  root = insertBST(root, 8);
  root = insertBST(root, 3);
  root = insertBST(root, 10);
  root = insertBST(root, 1);
  root = insertBST(root, 6);
  check(root && root->value == 8 && root->left->value == 3 &&
        root->right->value == 10);
  check(inorder(root) == vector<int>({1, 3, 6, 8, 10}));
  TreeNode *same = insertBST(root, 3);
  check(same == root && inorder(root) == vector<int>({1, 3, 6, 8, 10}));
  destroy(root);
  root = insertBST(nullptr, 0);
  check(root->value == 0);
  destroy(root);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed != total;
}

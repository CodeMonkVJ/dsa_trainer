#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

static TreeNode *insert(TreeNode *r, int v) {
  if (!r)
    return new TreeNode(v);
  if (v < r->value)
    r->left = insert(r->left, v);
  else
    r->right = insert(r->right, v);
  return r;
}
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
  for (int v : {8, 3, 10, 1, 6, 4, 7, 14})
    root = insert(root, v);
  root = deleteBST(root, 1);
  check(inorder(root) == vector<int>({3, 4, 6, 7, 8, 10, 14}));
  root = deleteBST(root, 10);
  check(inorder(root) == vector<int>({3, 4, 6, 7, 8, 14}));
  root = deleteBST(root, 8);
  check(inorder(root) == vector<int>({3, 4, 6, 7, 14}));
  root = deleteBST(root, 99);
  check(inorder(root) == vector<int>({3, 4, 6, 7, 14}));
  root = deleteBST(root, 3);
  check(inorder(root) == vector<int>({4, 6, 7, 14}));
  destroy(root);
  check(deleteBST(nullptr, 1) == nullptr);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed != total;
}

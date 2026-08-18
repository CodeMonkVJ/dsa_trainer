#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int value; TreeNode *left, *right; TreeNode(int v): value(v), left(nullptr), right(nullptr) {} };

static TreeNode *build(const vector<int> &preorder, size_t *index, long long upper) {
  if (*index == preorder.size() || static_cast<long long>(preorder[*index]) >= upper) return nullptr;
  int value = preorder[(*index)++];
  TreeNode *root = new TreeNode(value);
  root->left = build(preorder, index, value);
  root->right = build(preorder, index, upper);
  return root;
}

TreeNode *constructBST(const vector<int> &preorder) {
  size_t index = 0;
  return build(preorder, &index, numeric_limits<long long>::max());
}

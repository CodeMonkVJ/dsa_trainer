#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

bool isPresent(TreeNode *root, int t) {
  if (root == nullptr)
    return false;
  if (root->val == t)
    return true;
  return isPresent(root->left, t) || isPresent(root->right, t);
}

TreeNode *recurse(TreeNode *root, int a, int b) {
  if (root == nullptr)
    return nullptr;
  if (a < root->val && b < root->val) {
    return recurse(root->left, a, b);
  }

  if (a > root->val && b > root->val) {
    return recurse(root->right, a, b);
  }

  return root;
}

TreeNode *lcaBST(TreeNode *root, int a, int b) {
  if (root == nullptr)
    return nullptr;
  if (!isPresent(root, a) || !isPresent(root, b))
    return nullptr;

  return recurse(root, a, b);
}

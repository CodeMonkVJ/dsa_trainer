#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int value;
  TreeNode *left;
  TreeNode *right;
};

bool isMirror(TreeNode *left, TreeNode *right) {
  if (left == nullptr && right == nullptr) {
    return true;
  }
  if (left == nullptr || right == nullptr) {
    return false;
  }
  if (left->value != right->value)
    return false;
  return isMirror(left->left, right->right) &&
         isMirror(left->right, right->left);
}

bool isSymmetric(TreeNode *root) {
  if (root == nullptr)
    return true;
  TreeNode *left = root->left;
  TreeNode *right = root->right;
  return isMirror(left, right);
}

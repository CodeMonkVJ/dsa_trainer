#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int value;
  TreeNode *left, *right;
  TreeNode(int v): value(v), left(nullptr), right(nullptr) {}
};

TreeNode *deleteBST(TreeNode *root, int key) {
  if (root == nullptr) return nullptr;
  if (key < root->value) root->left = deleteBST(root->left, key);
  else if (key > root->value) root->right = deleteBST(root->right, key);
  else {
    if (root->left == nullptr) { TreeNode *right = root->right; delete root; return right; }
    if (root->right == nullptr) { TreeNode *left = root->left; delete root; return left; }
    TreeNode *successor = root->right;
    while (successor->left != nullptr) successor = successor->left;
    root->value = successor->value;
    root->right = deleteBST(root->right, successor->value);
  }
  return root;
}

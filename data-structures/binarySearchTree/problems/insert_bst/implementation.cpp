#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int value;
  TreeNode *left, *right;
  TreeNode(int v): value(v), left(nullptr), right(nullptr) {}
};

TreeNode *insertBST(TreeNode *root, int key) {
  if (root == nullptr) return new TreeNode(key);
  if (key < root->value) root->left = insertBST(root->left, key);
  else if (key > root->value) root->right = insertBST(root->right, key);
  return root;
}

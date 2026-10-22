#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

void flatten(TreeNode *root) {
  TreeNode *curr = root;

  while (curr != nullptr) {
    if (curr->left != nullptr) {
      TreeNode *rightMost = curr->left;
      while (rightMost->right != nullptr)
        rightMost = rightMost->right;

      rightMost->right = curr->right;
      curr->right = curr->left;
      curr->left = nullptr;
    }

    curr = curr->right;
  }

  return;
}

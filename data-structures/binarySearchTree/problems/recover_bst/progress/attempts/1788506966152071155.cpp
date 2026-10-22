#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void inOrderTraversal(TreeNode *root, vector<TreeNode *> &traversal) {
  if (root == nullptr)
    return;
  inOrderTraversal(root->left, traversal);
  traversal.push_back(root);
  inOrderTraversal(root->right, traversal);
}

void recoverBST(TreeNode *root) {
  vector<TreeNode *> traversal;
  inOrderTraversal(root, traversal);

  TreeNode *prev = nullptr, *first = nullptr, *second = nullptr;
  bool firstViolation = true;
  for (auto curr : traversal) {
    if (prev != nullptr && prev->val > curr->val) {
      if (firstViolation) {
        first = prev;
        second = curr;
        firstViolation = false;
      } else {
        second = curr;
      }
    }
    prev = curr;
  }

  if (first != nullptr && second != nullptr) {
    swap(first->val, second->val);
  }
}

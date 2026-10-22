#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

int recurse(TreeNode *root, int &diameter) {
  if (root == nullptr)
    return 0;
  int left = recurse(root->left, diameter);
  int right = recurse(root->right, diameter);

  diameter = max(diameter, left + right);
  return 1 + max(left, right);
}

int treeDiameter(TreeNode *root) {
  int diameter = 0;

  recurse(root, diameter);

  return diameter;
}

#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} };
static bool contains(TreeNode *root, int key) {
  while (root) { if (root->val == key) return true; root = key < root->val ? root->left : root->right; }
  return false;
}
TreeNode *lcaBST(TreeNode *root, int a, int b) {
  if (!root || !contains(root, a) || !contains(root, b)) return nullptr;
  while (root) {
    if (a < root->val && b < root->val) root = root->left;
    else if (a > root->val && b > root->val) root = root->right;
    else return root;
  }
  return nullptr;
}

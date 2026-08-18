#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} };
static bool valid(TreeNode *node, long long low, long long high) {
  if (!node) return true;
  if (node->val <= low || node->val >= high) return false;
  return valid(node->left, low, node->val) && valid(node->right, node->val, high);
}
bool isValidBST(TreeNode *root) { return valid(root, LLONG_MIN, LLONG_MAX); }

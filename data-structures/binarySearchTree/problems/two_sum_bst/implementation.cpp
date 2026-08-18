#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int value; TreeNode *left, *right; TreeNode(int v): value(v), left(nullptr), right(nullptr) {} };

bool findTarget(TreeNode *root, int target) {
  unordered_set<int> seen;
  stack<TreeNode *> pending;
  if (root != nullptr) pending.push(root);
  while (!pending.empty()) {
    TreeNode *node = pending.top(); pending.pop();
    if (seen.find(target - node->value) != seen.end()) return true;
    seen.insert(node->value);
    if (node->left != nullptr) pending.push(node->left);
    if (node->right != nullptr) pending.push(node->right);
  }
  return false;
}

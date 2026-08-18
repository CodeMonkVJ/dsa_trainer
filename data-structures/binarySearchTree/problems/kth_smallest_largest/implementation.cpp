#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int value; TreeNode *left, *right; TreeNode(int v): value(v), left(nullptr), right(nullptr) {} };

pair<int, int> kthSmallestLargest(TreeNode *root, int k) {
  vector<int> values;
  vector<TreeNode *> stack;
  TreeNode *current = root;
  while (current != nullptr || !stack.empty()) {
    while (current != nullptr) { stack.push_back(current); current = current->left; }
    current = stack.back(); stack.pop_back();
    values.push_back(current->value);
    current = current->right;
  }
  return {values[static_cast<size_t>(k - 1)], values[values.size() - static_cast<size_t>(k)]};
}

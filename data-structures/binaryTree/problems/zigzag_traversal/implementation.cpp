#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int v) : val(v), left(nullptr), right(nullptr) {} };

vector<vector<int>> zigzagTraversal(TreeNode* root) {
  vector<vector<int>> result;
  if (!root) return result;
  queue<TreeNode*> nodes; nodes.push(root); bool reverse = false;
  while (!nodes.empty()) {
    int size = (int)nodes.size(); vector<int> level(size);
    for (int i = 0; i < size; ++i) {
      TreeNode* node = nodes.front(); nodes.pop();
      level[reverse ? size - 1 - i : i] = node->val;
      if (node->left) nodes.push(node->left);
      if (node->right) nodes.push(node->right);
    }
    result.push_back(move(level)); reverse = !reverse;
  }
  return result;
}

int main() { return 0; }

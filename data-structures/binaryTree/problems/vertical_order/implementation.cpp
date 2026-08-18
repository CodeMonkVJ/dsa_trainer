#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int v) : val(v), left(nullptr), right(nullptr) {} };

vector<vector<int>> verticalOrder(TreeNode* root) {
  vector<vector<int>> result;
  if (!root) return result;
  map<int, vector<int>> columns; queue<pair<TreeNode*, int>> nodes; nodes.push({root, 0});
  while (!nodes.empty()) {
    auto [node, column] = nodes.front(); nodes.pop(); columns[column].push_back(node->val);
    if (node->left) nodes.push({node->left, column - 1});
    if (node->right) nodes.push({node->right, column + 1});
  }
  for (auto& [column, values] : columns) result.push_back(move(values));
  return result;
}

int main() { return 0; }

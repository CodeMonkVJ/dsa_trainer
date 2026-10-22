#include <bits/stdc++.h>
#include <utility>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

vector<vector<int>> verticalOrder(TreeNode *root) {
  vector<vector<int>> ans;

  map<int, vector<int>> columns;

  if (root == nullptr)
    return {};

  queue<pair<TreeNode *, int>> q;
  q.push(make_pair(root, 0));

  while (!q.empty()) {
    auto [node, col] = q.front();
    q.pop();

    columns[col].push_back(node->val);

    if (node->left != nullptr)
      q.push(make_pair(node->left, col - 1));
    if (node->right != nullptr)
      q.push(make_pair(node->right, col + 1));
  }

  for (auto &[col, values] : columns) {
    ans.push_back(values);
  }

  return ans;
}

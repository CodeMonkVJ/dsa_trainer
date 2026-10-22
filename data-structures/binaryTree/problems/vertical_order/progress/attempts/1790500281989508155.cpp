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
  map<int, vector<int>> ansMap;
  queue<pair<int, TreeNode *>> q;

  if (root == nullptr)
    return {};

  q.push(make_pair(0, root));
  while (!q.empty()) {
    auto [col, node] = q.front();
    q.pop();

    ansMap[col].push_back(node->val);

    if (node->left != nullptr)
      q.push(make_pair(col - 1, node->left));
    if (node->right != nullptr)
      q.push(make_pair(col + 1, node->right));
  }

  for (auto &[col, values] : ansMap) {
    ans.push_back(values);
  }

  return ans;
}

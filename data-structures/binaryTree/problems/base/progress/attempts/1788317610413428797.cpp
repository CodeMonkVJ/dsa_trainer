#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int value;
  TreeNode *left;
  TreeNode *right;
};

vector<vector<int>> levelOrder(TreeNode *root) {
  vector<vector<int>> ans;
  if (root == nullptr)
    return ans;

  queue<TreeNode *> q;
  q.push(root);
  while (!q.empty()) {
    int levelSize = q.size();
    vector<int> currLevel;
    while (levelSize--) {
      TreeNode *curr = q.front();
      if (curr->left)
        q.push(curr->left);
      if (curr->right)
        q.push(curr->right);
      currLevel.push_back(curr->value);
      q.pop();
    }
    ans.push_back(currLevel);
  }

  return ans;
}

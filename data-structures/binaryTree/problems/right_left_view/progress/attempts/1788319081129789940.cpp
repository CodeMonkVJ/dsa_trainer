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

vector<int> leftView(TreeNode *root) {
  vector<int> ans;
  vector<vector<int>> lvl = levelOrder(root);

  for (int i = 0; i < lvl.size(); i++) {
    ans.push_back(lvl[i][0]);
  }

  return ans;
}

vector<int> rightView(TreeNode *root) {
  vector<int> ans;
  vector<vector<int>> lvl = levelOrder(root);

  for (int i = 0; i < lvl.size(); i++) {
    int n = lvl[i].size();
    ans.push_back(lvl[i][n - 1]);
  }

  return ans;
}

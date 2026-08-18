#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int value; TreeNode* left; TreeNode* right; };
vector<vector<int>> levelOrder(TreeNode* root) {
  vector<vector<int>> result; if (!root) return result;
  queue<TreeNode*> q; q.push(root);
  while (!q.empty()) { int n = (int)q.size(); result.push_back({});
    while (n--) { TreeNode* node = q.front(); q.pop(); result.back().push_back(node->value);
      if (node->left) q.push(node->left);
      if (node->right) q.push(node->right);
    }
  } return result;
}

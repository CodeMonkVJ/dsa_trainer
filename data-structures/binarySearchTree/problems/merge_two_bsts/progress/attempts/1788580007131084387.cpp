#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void inOrderTraversal(TreeNode *root, vector<int> &traversal) {
  if (root == nullptr)
    return;
  inOrderTraversal(root->left, traversal);
  traversal.push_back(root->val);
  inOrderTraversal(root->right, traversal);
}

vector<int> mergeBSTs(TreeNode *root1, TreeNode *root2) {
  if (root1 == nullptr && root2 == nullptr)
    return {};
  vector<int> ans;

  inOrderTraversal(root1, ans);
  inOrderTraversal(root2, ans);

  sort(ans.begin(), ans.end());
  return ans;
}

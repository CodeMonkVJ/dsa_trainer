#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

int recurse(TreeNode *root, int &ans) {
  if (root == nullptr)
    return 0;
  int bestLeft = max(0, recurse(root->left, ans));
  int bestRight = max(0, recurse(root->right, ans));

  ans = max(ans, root->val + bestRight + bestLeft);

  return root->val + max(bestLeft, bestRight);
}

int maxPathSum(TreeNode *root) {
  if (root == nullptr)
    return INT_MIN;

  int ans = INT_MIN;
  recurse(root, ans);

  return ans;
}

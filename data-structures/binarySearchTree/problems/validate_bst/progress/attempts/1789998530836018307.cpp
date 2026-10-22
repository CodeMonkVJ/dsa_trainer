#include <bits/stdc++.h>
#include <climits>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

bool recurse(TreeNode *root, long lowerBound, long upperBound) {
  if (root == nullptr)
    return true;
  if (root->val > lowerBound && root->val < upperBound) {
    return recurse(root->left, lowerBound, root->val) &&
           recurse(root->right, root->val, upperBound);
  }

  return false;
}

bool isValidBST(TreeNode *root) { return recurse(root, LONG_MIN, LONG_MAX); }

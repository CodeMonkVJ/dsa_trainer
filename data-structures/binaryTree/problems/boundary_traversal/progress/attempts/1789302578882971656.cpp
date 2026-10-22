#include <bits/stdc++.h>
#include <vector>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

bool isLeaf(TreeNode *root) {
  if (root != nullptr && root->left == nullptr && root->right == nullptr)
    return true;

  return false;
}

void buildLeft(TreeNode *root, vector<int> &ans) {
  if (root == nullptr)
    return;
  if (isLeaf(root))
    return;
  ans.push_back(root->val);
  if (root->left != nullptr) {
    buildLeft(root->left, ans);
  } else if (root->right != nullptr) {
    buildLeft(root->right, ans);
  }
}

void buildLeaves(TreeNode *root, vector<int> &ans) {
  if (root == nullptr)
    return;
  if (isLeaf(root)) {
    ans.push_back(root->val);
  } else {
    buildLeaves(root->left, ans);
    buildLeaves(root->right, ans);
  }
}

void buildRight(TreeNode *root, vector<int> &ans) {
  if (root == nullptr)
    return;
  if (isLeaf(root))
    return;
  if (root->right != nullptr) {
    buildRight(root->right, ans);
  } else if (root->left != nullptr) {
    buildRight(root->left, ans);
  }
  ans.push_back(root->val);
}

vector<int> boundaryTraversal(TreeNode *root) {
  if (root == nullptr)
    return {};
  if (root->left == nullptr && root->right == nullptr)
    return {root->val};

  vector<int> ans;
  ans.push_back(root->val);

  buildLeft(root->left, ans);
  buildLeaves(root, ans);
  buildRight(root->right, ans);

  return ans;
}

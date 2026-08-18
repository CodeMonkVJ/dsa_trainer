#include <bits/stdc++.h>
using namespace std;
struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};
struct Traversals {
  vector<int> preorder, inorder, postorder;
};
Traversals allTraversals(TreeNode *root) { return {}; }

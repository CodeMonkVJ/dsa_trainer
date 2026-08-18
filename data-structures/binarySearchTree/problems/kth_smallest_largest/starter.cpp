#include <bits/stdc++.h>
using namespace std;
struct TreeNode {
  int value;
  TreeNode *left, *right;
  TreeNode(int v) : value(v), left(nullptr), right(nullptr) {}
};
pair<int, int> kthSmallestLargest(TreeNode *root, int k) { return {0, 0}; }

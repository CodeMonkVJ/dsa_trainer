#include <bits/stdc++.h>
using namespace std;
struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
pair<TreeNode *, TreeNode *> inorderSuccessorPredecessor(TreeNode *root,
                                                         int key) {
  return {nullptr, nullptr};
}

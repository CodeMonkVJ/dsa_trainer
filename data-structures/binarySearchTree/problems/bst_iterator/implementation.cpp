#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int value; TreeNode *left, *right; TreeNode(int v): value(v), left(nullptr), right(nullptr) {} };

class BSTIterator {
  stack<TreeNode *> pending;
  void pushLeft(TreeNode *node) { while (node != nullptr) { pending.push(node); node = node->left; } }
public:
  explicit BSTIterator(TreeNode *root) { pushLeft(root); }
  bool hasNext() const { return !pending.empty(); }
  int next() {
    TreeNode *node = pending.top(); pending.pop();
    pushLeft(node->right);
    return node->value;
  }
};

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int value;
  TreeNode *left, *right;
  TreeNode(int v) : value(v), left(nullptr), right(nullptr) {}
};

class BSTIterator {
public:
  stack<TreeNode *> st;

  void pushLeft(TreeNode *node) {
    while (node != nullptr) {
      st.push(node);
      node = node->left;
    }
  }

  explicit BSTIterator(TreeNode *root) { pushLeft(root); }

  bool hasNext() const { return !st.empty(); }

  int next() {
    TreeNode *node = st.top();
    st.pop();
    if (node->right != nullptr) {
      pushLeft(node->right);
    }
    return node->value;
  }
};

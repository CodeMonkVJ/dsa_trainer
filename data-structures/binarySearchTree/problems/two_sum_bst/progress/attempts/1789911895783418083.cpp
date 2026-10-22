#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int value;
  TreeNode *left, *right;
  TreeNode(int v) : value(v), left(nullptr), right(nullptr) {}
};

TreeNode *nextLargest(stack<TreeNode *> &st) {
  if (st.empty())
    return nullptr;
  TreeNode *top = st.top();
  st.pop();
  TreeNode *curr = top->left;
  while (curr != nullptr) {
    st.push(curr);
    curr = curr->right;
  }

  return top;
}

TreeNode *nextSmallest(stack<TreeNode *> &st) {
  if (st.empty())
    return nullptr;
  TreeNode *top = st.top();
  st.pop();
  TreeNode *curr = top->right;
  while (curr != nullptr) {
    st.push(curr);
    curr = curr->left;
  }

  return top;
}

bool findTarget(TreeNode *root, int target) {
  if (root == nullptr)
    return false;
  stack<TreeNode *> minStack;
  stack<TreeNode *> maxStack;

  TreeNode *curr = root;
  while (curr != nullptr) {
    maxStack.push(curr);
    curr = curr->right;
  }
  curr = root;
  while (curr != nullptr) {
    minStack.push(curr);
    curr = curr->left;
  }

  TreeNode *left = minStack.top();
  TreeNode *right = maxStack.top();

  while (left != right) {
    long long sum = left->value + right->value;
    if (sum < target) {
      left = nextSmallest(minStack);
    } else if (sum > target) {
      right = nextLargest(maxStack);
    } else {
      return true;
    }
  }

  return false;
}

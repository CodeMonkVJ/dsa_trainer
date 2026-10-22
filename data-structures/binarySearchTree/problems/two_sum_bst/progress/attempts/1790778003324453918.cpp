#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int value;
  TreeNode *left, *right;
  TreeNode(int v) : value(v), left(nullptr), right(nullptr) {}
};

TreeNode *getNextMin(stack<TreeNode *> &minStack) {
  if (minStack.empty())
    return nullptr;
  TreeNode *top = minStack.top();
  minStack.pop();
  TreeNode *right = top->right;
  while (right != nullptr) {
    minStack.push(right);
    right = right->left;
  }
  return top;
}

TreeNode *getNextMax(stack<TreeNode *> &maxStack) {
  if (maxStack.empty())
    return nullptr;
  TreeNode *top = maxStack.top();
  maxStack.pop();
  TreeNode *left = top->left;
  while (left != nullptr) {
    maxStack.push(left);
    left = left->right;
  }
  return top;
}

bool findTarget(TreeNode *root, int target) {
  stack<TreeNode *> minStack;
  stack<TreeNode *> maxStack;
  TreeNode *curr = root;
  while (curr != nullptr) {
    minStack.push(curr);
    curr = curr->left;
  }
  curr = root;
  while (curr != nullptr) {
    maxStack.push(curr);
    curr = curr->right;
  }
  TreeNode *left = getNextMin(minStack);
  TreeNode *right = getNextMax(maxStack);

  while (left != nullptr && right != nullptr && left != right) {
    int sum = left->value + right->value;

    if (sum == target)
      return true;
    else if (sum < target) {
      left = getNextMin(minStack);
    } else {
      right = getNextMax(maxStack);
    }
  }

  return false;
}

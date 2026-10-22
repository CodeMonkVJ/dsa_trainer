#include <bits/stdc++.h>
using namespace std;

struct NodeState {
  bool isBST;
  int size;
  long long min;
  long long max;
  int largestBST;
  NodeState()
      : isBST(false), size(0), min(LLONG_MAX), max(LLONG_MIN), largestBST(0) {}
  NodeState(bool isBST, size_t size, long long min, long long max,
            int largestBST)
      : isBST(isBST), size(size), min(min), max(max), largestBST(largestBST) {}
};

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

NodeState recurse(TreeNode *root) {
  if (root == nullptr)
    return {true, 0, LLONG_MAX, LLONG_MIN, 0};
  NodeState leftState = recurse(root->left);
  NodeState rightState = recurse(root->right);
  NodeState currState;

  if (leftState.isBST && rightState.isBST && leftState.max < root->val &&
      root->val < rightState.min) {
    currState.isBST = true;
    currState.size = leftState.size + rightState.size + 1;
    currState.min = min<long long>(root->val, leftState.min);
    currState.max = max<long long>(root->val, rightState.max);
    currState.largestBST = currState.size;
  } else {
    currState.isBST = false;
    currState.largestBST = max(leftState.largestBST, rightState.largestBST);
  }

  return currState;
}

int largestBST(TreeNode *root) { return recurse(root).largestBST; }

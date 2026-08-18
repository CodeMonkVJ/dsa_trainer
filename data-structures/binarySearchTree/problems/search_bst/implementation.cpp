#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int value;
  TreeNode *left, *right;
  TreeNode(int v): value(v), left(nullptr), right(nullptr) {}
};

bool searchBST(TreeNode *root, int key) {
  TreeNode *current = root;
  while (current != nullptr) {
    if (current->value == key) return true;
    current = key < current->value ? current->left : current->right;
  }
  return false;
}

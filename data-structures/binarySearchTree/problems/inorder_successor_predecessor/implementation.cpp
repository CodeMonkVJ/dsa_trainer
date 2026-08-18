#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} };
pair<TreeNode *, TreeNode *> inorderSuccessorPredecessor(TreeNode *root, int key) {
  TreeNode *predecessor=nullptr, *successor=nullptr;
  while (root) {
    if (root->val == key) {
      if (root->left) { predecessor=root->left; while (predecessor->right) predecessor=predecessor->right; }
      if (root->right) { successor=root->right; while (successor->left) successor=successor->left; }
      break;
    }
    if (root->val < key) { predecessor=root; root=root->right; }
    else { successor=root; root=root->left; }
  }
  return {predecessor, successor};
}

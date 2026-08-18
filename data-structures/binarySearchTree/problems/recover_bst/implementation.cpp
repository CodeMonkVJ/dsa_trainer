#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} };
void recoverBST(TreeNode* root) {
  TreeNode *first=nullptr, *second=nullptr, *previous=nullptr;
  auto visit = [&](TreeNode* node) { if (previous && previous->val > node->val) { if (!first) first=previous; second=node; } previous=node; };
  TreeNode* current=root;
  while (current) {
    if (!current->left) { visit(current); current=current->right; }
    else { TreeNode* pred=current->left; while (pred->right && pred->right != current) pred=pred->right;
      if (!pred->right) { pred->right=current; current=current->left; }
      else { pred->right=nullptr; visit(current); current=current->right; }
    }
  }
  if (first && second) swap(first->val, second->val);
}

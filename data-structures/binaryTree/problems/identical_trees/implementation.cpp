#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int v) : val(v), left(nullptr), right(nullptr) {} };

bool areIdentical(TreeNode* first, TreeNode* second) {
  if (!first || !second) return first == second;
  return first->val == second->val && areIdentical(first->left, second->left) && areIdentical(first->right, second->right);
}

int main() { return 0; }

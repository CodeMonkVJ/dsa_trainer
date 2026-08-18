#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} };
static void inorder(TreeNode* node, vector<int>& out) { if (!node) return; inorder(node->left, out); out.push_back(node->val); inorder(node->right, out); }
vector<int> mergeBSTs(TreeNode* root1, TreeNode* root2) {
  vector<int> a, b, result; inorder(root1, a); inorder(root2, b); result.reserve(a.size() + b.size());
  size_t i = 0, j = 0;
  while (i < a.size() || j < b.size()) {
    int value;
    if (j == b.size() || (i < a.size() && a[i] < b[j])) value = a[i++];
    else if (i == a.size() || b[j] < a[i]) value = b[j++];
    else { value = a[i++]; result.push_back(value); result.push_back(b[j++]); continue; }
    result.push_back(value);
  }
  return result;
}

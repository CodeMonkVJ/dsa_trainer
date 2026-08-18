#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int v) : val(v), left(nullptr), right(nullptr) {} };

static bool leaf(TreeNode* node) { return node && !node->left && !node->right; }
static void leaves(TreeNode* node, vector<int>& out) {
  if (!node) return;
  if (leaf(node)) { out.push_back(node->val); return; }
  leaves(node->left, out); leaves(node->right, out);
}

vector<int> boundaryTraversal(TreeNode* root) {
  vector<int> out;
  if (!root) return out;
  if (!leaf(root)) out.push_back(root->val);
  for (TreeNode* node = root->left; node; node = node->left ? node->left : node->right)
    if (!leaf(node)) out.push_back(node->val);
  leaves(root, out);
  vector<int> right;
  for (TreeNode* node = root->right; node; node = node->right ? node->right : node->left)
    if (!leaf(node)) right.push_back(node->val);
  reverse(right.begin(), right.end()); out.insert(out.end(), right.begin(), right.end());
  return out;
}

int main() { return 0; }

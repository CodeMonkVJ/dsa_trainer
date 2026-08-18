#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int value; TreeNode *left, *right; TreeNode(int v) : value(v), left(nullptr), right(nullptr) {} };
static void visit(TreeNode *node, vector<int> &out) { if (!node) return; visit(node->left, out); out.push_back(node->value); visit(node->right, out); }
vector<int> inorderTraversal(TreeNode *root) { vector<int> out; visit(root, out); return out; }
int main() { return 0; }

#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int value; TreeNode *left, *right; TreeNode(int v):value(v),left(nullptr),right(nullptr){} };
static void visit(TreeNode *n, vector<int>& out) { if (!n) return; visit(n->left,out); visit(n->right,out); out.push_back(n->value); }
vector<int> postorderTraversal(TreeNode *root) { vector<int> out; visit(root,out); return out; }
int main(){return 0;}

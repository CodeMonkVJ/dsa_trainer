#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int v):val(v),left(nullptr),right(nullptr){} };
int treeHeight(TreeNode* root) { if(!root)return 0; return 1+max(treeHeight(root->left),treeHeight(root->right)); }
int main(){return 0;}

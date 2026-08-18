#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode* left; TreeNode* right; TreeNode(int v): val(v), left(nullptr), right(nullptr) {} };
void flatten(TreeNode* root){while(root){if(root->left){TreeNode*p=root->left;while(p->right)p=p->right;p->right=root->right;root->right=root->left;root->left=nullptr;}root=root->right;}}

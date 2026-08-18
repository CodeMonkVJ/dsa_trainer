#include <bits/stdc++.h>
using namespace std; struct TreeNode { int value; TreeNode* left; TreeNode* right; };
bool mirror(TreeNode*a,TreeNode*b){if(!a||!b)return a==b;return a->value==b->value&&mirror(a->left,b->right)&&mirror(a->right,b->left);} bool isSymmetric(TreeNode*root){return !root||mirror(root->left,root->right);}

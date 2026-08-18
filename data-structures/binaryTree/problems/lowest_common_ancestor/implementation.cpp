#include <bits/stdc++.h>
using namespace std; struct TreeNode { int value; TreeNode* left; TreeNode* right; };
TreeNode* lca(TreeNode*n,int a,int b){if(!n||n->value==a||n->value==b)return n;TreeNode*l=lca(n->left,a,b),*r=lca(n->right,a,b);return l&&r?n:(l?l:r);}bool contains(TreeNode*n,int v){return n&&(n->value==v||contains(n->left,v)||contains(n->right,v));}optional<int> lowestCommonAncestor(TreeNode*root,int a,int b){if(!contains(root,a)||!contains(root,b))return nullopt;return lca(root,a,b)->value;}

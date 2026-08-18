#include <bits/stdc++.h>
using namespace std; struct TreeNode { int value; TreeNode* left; TreeNode* right; };
bool findPath(TreeNode*n,int t,vector<int>&p){if(!n)return false;p.push_back(n->value);if(n->value==t||findPath(n->left,t,p)||findPath(n->right,t,p))return true;p.pop_back();return false;} vector<int> rootToNodePath(TreeNode*root,int t){vector<int>p;findPath(root,t,p);return p;}

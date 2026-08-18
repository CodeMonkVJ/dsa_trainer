#include <bits/stdc++.h>
using namespace std; struct TreeNode { int value; TreeNode* left; TreeNode* right; };
vector<int> topView(TreeNode* root) { if(!root) return {}; map<int,int> seen; queue<pair<TreeNode*,int>> q; q.push({root,0}); while(!q.empty()){auto [n,d]=q.front();q.pop(); if(!seen.count(d)) seen[d]=n->value; if(n->left)q.push({n->left,d-1}); if(n->right)q.push({n->right,d+1});} vector<int> r; for(auto [d,v]:seen)r.push_back(v); return r; }

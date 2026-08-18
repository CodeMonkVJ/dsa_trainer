#include <bits/stdc++.h>
using namespace std; struct TreeNode { int value; TreeNode* left; TreeNode* right; };
vector<int> bottomView(TreeNode* root){if(!root)return{};map<int,pair<int,int>> m;queue<tuple<TreeNode*,int,int>>q;q.push({root,0,0});while(!q.empty()){auto[n,d,dep]=q.front();q.pop();if(!m.count(d)||dep>=m[d].first)m[d]={dep,n->value};if(n->left)q.push({n->left,d-1,dep+1});if(n->right)q.push({n->right,d+1,dep+1});}vector<int>r;for(auto [d,x]:m)r.push_back(x.second);return r;}

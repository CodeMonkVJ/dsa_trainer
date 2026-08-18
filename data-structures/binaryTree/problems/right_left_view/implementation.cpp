#include <bits/stdc++.h>
using namespace std; struct TreeNode { int value; TreeNode* left; TreeNode* right; };
vector<int> leftView(TreeNode* root){vector<int>r;if(!root)return r;queue<TreeNode*>q;q.push(root);while(!q.empty()){int n=q.size();for(int i=0;i<n;i++){auto*x=q.front();q.pop();if(i==0)r.push_back(x->value);if(x->left)q.push(x->left);if(x->right)q.push(x->right);}}return r;}
vector<int> rightView(TreeNode* root){vector<int>r;if(!root)return r;queue<TreeNode*>q;q.push(root);while(!q.empty()){int n=q.size();for(int i=0;i<n;i++){auto*x=q.front();q.pop();if(i==n-1)r.push_back(x->value);if(x->left)q.push(x->left);if(x->right)q.push(x->right);}}return r;}

#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode* left; TreeNode* right; TreeNode(int v): val(v), left(nullptr), right(nullptr) {} };
vector<int> morrisInorder(TreeNode* root){vector<int> out;while(root){if(!root->left){out.push_back(root->val);root=root->right;}else{TreeNode*p=root->left;while(p->right&&p->right!=root)p=p->right;if(!p->right){p->right=root;root=root->left;}else{p->right=nullptr;out.push_back(root->val);root=root->right;}}}return out;}

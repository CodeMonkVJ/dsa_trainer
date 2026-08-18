#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int v):val(v),left(nullptr),right(nullptr){} };
struct Traversals { vector<int> preorder, inorder, postorder; };
Traversals allTraversals(TreeNode* root) {
    Traversals out; if(!root) return out; stack<pair<TreeNode*,int>> st; st.push({root,1});
    while(!st.empty()){auto [node,state]=st.top();st.pop(); if(state==1){out.preorder.push_back(node->val);st.push({node,2});if(node->left)st.push({node->left,1});} else if(state==2){out.inorder.push_back(node->val);st.push({node,3});if(node->right)st.push({node->right,1});} else out.postorder.push_back(node->val);}
    return out;
}
int main(){return 0;}

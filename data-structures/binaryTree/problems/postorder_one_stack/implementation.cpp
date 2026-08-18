#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int v):val(v),left(nullptr),right(nullptr){} };
vector<int> postorderOneStack(TreeNode* root) {
    vector<int> result; stack<TreeNode*> nodes; TreeNode* current=root; TreeNode* last=nullptr;
    while(current || !nodes.empty()) { if(current){nodes.push(current);current=current->left;} else {TreeNode* peek=nodes.top(); if(peek->right && last!=peek->right) current=peek->right; else {result.push_back(peek->val);last=peek;nodes.pop();}} }
    return result;
}
int main(){return 0;}

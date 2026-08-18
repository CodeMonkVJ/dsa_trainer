#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int v):val(v),left(nullptr),right(nullptr){} };
vector<int> postorderTwoStacks(TreeNode* root) {
    if (!root) return {};
    stack<TreeNode*> first, second; vector<int> result; first.push(root);
    while (!first.empty()) { TreeNode* node=first.top(); first.pop(); second.push(node); if(node->left) first.push(node->left); if(node->right) first.push(node->right); }
    while (!second.empty()) { result.push_back(second.top()->val); second.pop(); }
    return result;
}
int main(){return 0;}

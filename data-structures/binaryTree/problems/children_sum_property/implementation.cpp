#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int v): val(v), left(nullptr), right(nullptr) {} };

TreeNode* enforceChildrenSum(TreeNode* root) {
    if (!root || (!root->left && !root->right)) return root;
    enforceChildrenSum(root->left); enforceChildrenSum(root->right);
    int childSum = (root->left ? root->left->val : 0) + (root->right ? root->right->val : 0);
    if (childSum >= root->val) root->val = childSum;
    else {
        root->val = root->val;
        if (root->left) root->left->val = root->val;
        else root->right->val = root->val;
        enforceChildrenSum(root->left); enforceChildrenSum(root->right);
    }
    return root;
}

int main(){TreeNode r(10);r.left=new TreeNode(8);r.right=new TreeNode(2);enforceChildrenSum(&r);cout<<r.val<<'\n';return 0;}

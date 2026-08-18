#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int v): val(v), left(nullptr), right(nullptr) {} };

int countNodes(TreeNode* root) {
    if (!root) return 0;
    int leftHeight=0,rightHeight=0; for(TreeNode*n=root;n;n=n->left)++leftHeight; for(TreeNode*n=root;n;n=n->right)++rightHeight;
    if (leftHeight==rightHeight) return (1<<leftHeight)-1;
    return 1+countNodes(root->left)+countNodes(root->right);
}

int main(){TreeNode r(1);r.left=new TreeNode(2);r.right=new TreeNode(3);cout<<countNodes(&r)<<'\n';return 0;}

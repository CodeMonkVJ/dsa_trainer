#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int v):val(v),left(nullptr),right(nullptr){} };
int diameterHeight(TreeNode* node,int& best){if(!node)return 0;int left=diameterHeight(node->left,best),right=diameterHeight(node->right,best);best=max(best,left+right);return 1+max(left,right);}
int treeDiameter(TreeNode* root){int best=0;diameterHeight(root,best);return best;}
int main(){return 0;}

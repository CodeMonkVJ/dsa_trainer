#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int v):val(v),left(nullptr),right(nullptr){} };
int balancedHeight(TreeNode* node){if(!node)return 0;int left=balancedHeight(node->left);if(left<0)return -1;int right=balancedHeight(node->right);if(right<0||abs(left-right)>1)return -1;return 1+max(left,right);}
bool isBalanced(TreeNode* root){return balancedHeight(root)>=0;}
int main(){return 0;}

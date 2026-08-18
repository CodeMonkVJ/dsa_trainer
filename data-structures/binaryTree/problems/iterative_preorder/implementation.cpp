#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int value; TreeNode *left, *right; TreeNode(int v):value(v),left(nullptr),right(nullptr){} };
vector<int> iterativePreorder(TreeNode *root) { vector<int> out; if(!root)return out; stack<TreeNode*> st;st.push(root);while(!st.empty()){auto*n=st.top();st.pop();out.push_back(n->value);if(n->right)st.push(n->right);if(n->left)st.push(n->left);}return out; }
int main(){return 0;}

#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int value; TreeNode *left, *right; TreeNode(int v):value(v),left(nullptr),right(nullptr){} };
vector<int> iterativeInorder(TreeNode *root) { vector<int> out; stack<TreeNode*> st;auto*n=root;while(n||!st.empty()){while(n){st.push(n);n=n->left;}n=st.top();st.pop();out.push_back(n->value);n=n->right;}return out; }
int main(){return 0;}

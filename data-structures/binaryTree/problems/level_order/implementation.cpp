#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int value; TreeNode *left, *right; TreeNode(int v):value(v),left(nullptr),right(nullptr){} };
vector<vector<int>> levelOrder(TreeNode *root) { vector<vector<int>> out; if(!root)return out; queue<TreeNode*> q; q.push(root); while(!q.empty()){int n=q.size();out.push_back({});while(n--){auto*x=q.front();q.pop();out.back().push_back(x->value);if(x->left)q.push(x->left);if(x->right)q.push(x->right);}}return out; }
int main(){return 0;}

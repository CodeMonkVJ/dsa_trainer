#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int v): val(v), left(nullptr), right(nullptr) {} };

int burnTime(TreeNode* root, int target) {
    if (!root) return -1;
    unordered_map<TreeNode*, TreeNode*> parent; TreeNode* start = nullptr;
    queue<TreeNode*> build; build.push(root); parent[root] = nullptr;
    while (!build.empty()) { TreeNode* n=build.front();build.pop(); if(n->val==target)start=n; if(n->left)parent[n->left]=n,build.push(n->left); if(n->right)parent[n->right]=n,build.push(n->right); }
    if (!start) return -1;
    queue<TreeNode*> q; unordered_set<TreeNode*> seen; q.push(start); seen.insert(start); int minutes=-1;
    while (!q.empty()) { int count=q.size(); ++minutes; while(count--){TreeNode*n=q.front();q.pop();for(TreeNode* next:{n->left,n->right,parent[n]})if(next&&seen.insert(next).second)q.push(next);} }
    return minutes;
}

int main(){TreeNode r(1);r.left=new TreeNode(2);r.right=new TreeNode(3);cout<<burnTime(&r,2)<<'\n';return 0;}

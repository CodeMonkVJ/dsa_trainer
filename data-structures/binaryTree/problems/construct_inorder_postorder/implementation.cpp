#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode* left; TreeNode* right; TreeNode(int v): val(v), left(nullptr), right(nullptr) {} };
TreeNode* buildTree(const vector<int>& inorder, const vector<int>& postorder) {
    if (inorder.size()!=postorder.size() || inorder.empty()) return nullptr;
    unordered_map<int,int> at; for (int i=0;i<(int)inorder.size();++i) at[inorder[i]]=i;
    function<TreeNode*(int,int,int,int)> make=[&](int il,int ir,int pl,int pr)->TreeNode* {
        if(il>=ir||pl>=pr) return nullptr;
        auto it=at.find(postorder[pr-1]);
        if(it==at.end()||it->second<il||it->second>=ir) return nullptr;
        int mid=it->second,left=mid-il; TreeNode* n=new TreeNode(postorder[pr-1]);
        n->left=make(il,mid,pl,pl+left); n->right=make(mid+1,ir,pl+left,pr-1); return n;
    }; return make(0,(int)inorder.size(),0,(int)postorder.size());
}

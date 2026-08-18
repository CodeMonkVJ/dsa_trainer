#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} };
static TreeNode* build(const vector<int>& a,int lo,int hi){if(lo>hi)return nullptr;int mid=lo+(hi-lo)/2;auto*x=new TreeNode(a[mid]);x->left=build(a,lo,mid-1);x->right=build(a,mid+1,hi);return x;}
TreeNode* constructBST(const vector<int>& keys){return build(keys,0,(int)keys.size()-1);}

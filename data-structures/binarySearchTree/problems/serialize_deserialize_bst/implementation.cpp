#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} };
string serializeBST(TreeNode* root) { vector<int> values; function<void(TreeNode*)> dfs=[&](TreeNode*x){if(!x)return;values.push_back(x->val);dfs(x->left);dfs(x->right);};dfs(root); stringstream out; for(size_t i=0;i<values.size();++i){if(i)out<<' ';out<<values[i];} return out.str(); }
TreeNode* deserializeBST(const string& data) { stringstream in(data); vector<int> a; int x; while(in>>x)a.push_back(x); size_t pos=0; function<TreeNode*(long long,long long)> build=[&](long long lo,long long hi)->TreeNode*{if(pos==a.size()||a[pos]<=lo||a[pos]>=hi)return nullptr;int v=a[pos++];auto*node=new TreeNode(v);node->left=build(lo,v);node->right=build(v,hi);return node;};return build(LLONG_MIN,LLONG_MAX); }

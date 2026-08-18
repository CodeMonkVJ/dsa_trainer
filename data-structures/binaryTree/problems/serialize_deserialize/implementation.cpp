#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode* left; TreeNode* right; TreeNode(int v): val(v), left(nullptr), right(nullptr) {} };
string serialize(TreeNode* root){string out;function<void(TreeNode*)> go=[&](TreeNode*n){if(!n){out+="# ";return;}out+=to_string(n->val)+" ";go(n->left);go(n->right);};go(root);return out;}
TreeNode* deserialize(const string& data){istringstream in(data);function<TreeNode*()>go=[&](){string s;if(!(in>>s)||s=="#")return (TreeNode*)nullptr;TreeNode*n=new TreeNode(stoi(s));n->left=go();n->right=go();return n;};return go();}

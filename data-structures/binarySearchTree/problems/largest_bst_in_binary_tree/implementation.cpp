#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} };
struct Info { bool valid; int size; long long low, high; };
static Info solve(TreeNode* node) {
  if (!node) return {true,0,LLONG_MAX,LLONG_MIN};
  Info l=solve(node->left), r=solve(node->right);
  if (l.valid && r.valid && l.high < node->val && node->val < r.low)
    return {true,l.size+r.size+1,min(l.low,(long long)node->val),max(r.high,(long long)node->val)};
  return {false,max(l.size,r.size),0,0};
}
int largestBST(TreeNode* root) { return solve(root).size; }

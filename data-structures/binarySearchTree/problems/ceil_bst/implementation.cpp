#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} };
int findCeil(TreeNode *root, int target) {
  int answer = -1;
  while (root) {
    if (root->val == target) return target;
    if (root->val > target) { answer = root->val; root = root->left; }
    else root = root->right;
  }
  return answer;
}

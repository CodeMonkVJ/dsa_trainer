#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int v) : val(v), left(nullptr), right(nullptr) {} };

static int bestDown(TreeNode* node, int& answer) {
  if (!node) return 0;
  int left = max(0, bestDown(node->left, answer));
  int right = max(0, bestDown(node->right, answer));
  answer = max(answer, node->val + left + right);
  return node->val + max(left, right);
}

int maxPathSum(TreeNode* root) {
  int answer = numeric_limits<int>::min();
  if (root) bestDown(root, answer);
  return answer;
}

int main() { return 0; }

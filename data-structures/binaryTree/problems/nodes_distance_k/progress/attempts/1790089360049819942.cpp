#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

void recurse(TreeNode *curr, unordered_map<TreeNode *, TreeNode *> &parents,
             const int k, TreeNode *&target) {
  if (curr->val == k) {
    target = curr;
  }
  if (curr->left != nullptr) {
    parents[curr->left] = curr;
    recurse(curr->left, parents, k, target);
  }
  if (curr->right != nullptr) {
    parents[curr->right] = curr;
    recurse(curr->right, parents, k, target);
  }
}

vector<int> nodesAtDistanceK(TreeNode *root, int target, int k) {
  if (root == nullptr || k < 0)
    return {};

  unordered_map<TreeNode *, TreeNode *> parents;
  TreeNode *targetNode = nullptr;

  parents[root] = nullptr;
  recurse(root, parents, target, targetNode);

  if (targetNode == nullptr) {
    return {};
  }

  vector<int> ans;
  queue<TreeNode *> q;
  set<TreeNode *> visited;

  int dist = 0;
  q.push(targetNode);
  visited.insert(targetNode);

  while (!q.empty()) {
    int sz = q.size();
    while (sz--) {
      TreeNode *curr = q.front();
      if (dist == k) {
        ans.push_back(curr->val);
      }
      q.pop();
      vector<TreeNode *> neighbors = {curr->left, curr->right, parents[curr]};
      for (auto neighbor : neighbors) {
        if (neighbor != nullptr && visited.count(neighbor) == 0) {
          visited.insert(curr);
          q.push(neighbor);
        }
      }
    }
    dist++;
  }

  return ans;
}

#include <bits/stdc++.h>
#include <set>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

void traverse(TreeNode *root, unordered_map<TreeNode *, TreeNode *> &map,
              TreeNode *&targetNode, const int &target) {
  if (root == nullptr)
    return;
  if (root->left != nullptr)
    map[root->left] = root;
  if (root->right != nullptr)
    map[root->right] = root;

  if (root->val == target) {
    targetNode = root;
  }

  traverse(root->left, map, targetNode, target);
  traverse(root->right, map, targetNode, target);
}

int burnTime(TreeNode *root, int target) {
  TreeNode *targetNode = nullptr;
  TreeNode *curr = root;
  if (root == nullptr)
    return -1;
  unordered_map<TreeNode *, TreeNode *> parents;
  set<TreeNode *> visited;
  parents[root] = nullptr;

  traverse(root, parents, targetNode, target);

  if (targetNode == nullptr)
    return -1;

  queue<TreeNode *> q;
  q.push(targetNode);
  visited.insert(targetNode);
  int time = 0;

  while (!q.empty()) {
    int levelSize = q.size();
    bool spread = false;

    while (levelSize--) {
      TreeNode *curr = q.front();
      q.pop();

      vector<TreeNode *> neighbours = {curr->left, curr->right, parents[curr]};
      for (auto x : neighbours) {
        if (x != nullptr && visited.count(x) == 0) {
          q.push(x);
          visited.insert(x);
          spread = true;
        }
      }
    }

    if (spread)
      time++;
  }

  return time;
}

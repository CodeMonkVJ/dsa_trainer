#include <bits/stdc++.h>
using namespace std;
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};
string serialize(TreeNode *root) { return {}; }
TreeNode *deserialize(const string &) { return nullptr; }

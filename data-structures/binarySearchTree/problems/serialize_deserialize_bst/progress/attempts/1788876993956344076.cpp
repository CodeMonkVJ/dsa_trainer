#include <bits/stdc++.h>
#include <string>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void recursePreOrder(TreeNode *root, string &serialize) {
  if (root == nullptr)
    return;
  if (!serialize.empty())
    serialize += ' ';
  serialize += to_string(root->val);
  recursePreOrder(root->left, serialize);
  recursePreOrder(root->right, serialize);
}

string serializeBST(TreeNode *root) {
  string ans = "";
  recursePreOrder(root, ans);
  return ans;
}

queue<string> splitByString(string s, const string &delimiter) {
  queue<string> tokens;
  size_t pos = 0;
  if (s.length() == 0)
    return tokens;
  while ((pos = s.find(delimiter)) != string::npos) {
    tokens.push(s.substr(0, pos));
    s.erase(0, pos + delimiter.length());
  }
  tokens.push(s);
  return tokens;
}

TreeNode *build(int min, int max, queue<string> &values) {
  if (values.size() == 0)
    return nullptr;

  int x = stoi(values.front());
  if (x < min || x > max)
    return nullptr;

  values.pop();

  TreeNode *node = new TreeNode(x);
  node->left = build(min, x, values);
  node->right = build(x, max, values);

  return node;
}

TreeNode *deserializeBST(const string &data) {
  queue<string> values = splitByString(data, " ");
  return build(INT_MIN, INT_MAX, values);
}

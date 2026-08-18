#include <bits/stdc++.h>
using namespace std;
struct TreeNode {
  int value;
  TreeNode *left, *right;
  TreeNode(int v) : value(v), left(nullptr), right(nullptr) {}
};
class BSTIterator {
public:
  explicit BSTIterator(TreeNode *) {}
  bool hasNext() const { return false; }
  int next() { return 0; }
};

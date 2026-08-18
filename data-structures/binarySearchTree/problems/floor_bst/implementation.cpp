#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int value;
  TreeNode *left, *right;
  TreeNode(int v): value(v), left(nullptr), right(nullptr) {}
};

int floorBST(TreeNode *root, int key) {
  int answer = -1;
  TreeNode *current = root;
  while (current != nullptr) {
    if (current->value == key) return key;
    if (current->value < key) { answer = current->value; current = current->right; }
    else current = current->left;
  }
  return answer;
}

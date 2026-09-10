#include <bits/stdc++.h>
using namespace std;

struct Node {
  int data;
  Node *left, *right;
  Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

void recHelper(Node *node, Node *&prev, Node *&head) {
  if (node == nullptr)
    return;

  Node *originalRight = node->right;

  recHelper(node->left, prev, head);

  if (prev == nullptr) {
    head = node;
    node->left = nullptr;
  } else {
    prev->right = node;
    node->left = prev;
  }

  prev = node;

  recHelper(originalRight, prev, head);
}

Node *treeToDoublyList(Node *root) {
  if (root == nullptr)
    return root;

  Node *head = nullptr, *prev = nullptr;

  recHelper(root, prev, head);

  prev->right = nullptr;

  return head;
}

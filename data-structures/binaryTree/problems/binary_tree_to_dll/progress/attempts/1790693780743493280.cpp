#include <bits/stdc++.h>
using namespace std;

struct Node {
  int data;
  Node *left, *right;
  Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

void recurse(Node *root, Node *&prev, Node *&head) {
  if (root == nullptr)
    return;

  recurse(root->left, prev, head);

  if (prev == nullptr) {
    head = root;
  } else {
    prev->right = root;
    root->left = prev;
  }
  prev = root;

  recurse(root->right, prev, head);
}

Node *treeToDoublyList(Node *root) {
  Node *head = nullptr;
  Node *prev = nullptr;
  recurse(root, prev, head);

  return head;
}

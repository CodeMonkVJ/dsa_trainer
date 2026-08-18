#include <bits/stdc++.h>
using namespace std;
struct Node { int data; Node *left, *right; Node(int value): data(value), left(nullptr), right(nullptr) {} };
static void convert(Node* node, Node*& head, Node*& previous) {
    if (!node) return;
    convert(node->left, head, previous);
    if (!previous) head = node; else { previous->right = node; node->left = previous; }
    previous = node;
    convert(node->right, head, previous);
}
Node* treeToDoublyList(Node* root) { Node* head = nullptr; Node* previous = nullptr; convert(root, head, previous); if (previous) previous->right = nullptr; return head; }

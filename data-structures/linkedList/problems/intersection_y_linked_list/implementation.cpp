#include <bits/stdc++.h>
using namespace std;

struct Node {
  int value;
  Node* next;
  explicit Node(int value = 0) : value(value), next(nullptr) {}
};

// Switching heads after reaching the end equalizes the distance each pointer travels.
Node* getIntersectionNode(Node* headA, Node* headB) {
  Node* a = headA;
  Node* b = headB;
  while (a != b) {
    a = a == nullptr ? headB : a->next;
    b = b == nullptr ? headA : b->next;
  }
  return a;
}

int main() { return 0; }

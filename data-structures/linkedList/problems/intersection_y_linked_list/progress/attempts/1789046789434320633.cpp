#include <bits/stdc++.h>
using namespace std;

struct Node {
  int value;
  Node *next;
  explicit Node(int value = 0) : value(value), next(nullptr) {}
};

Node *getIntersectionNode(Node *headA, Node *headB) {
  Node *currA = headA;
  Node *currB = headB;

  while (currA != currB) {
    currA = (currA == nullptr) ? headB : currA->next;
    currB = (currB == nullptr) ? headA : currB->next;
  }

  return currA;
}

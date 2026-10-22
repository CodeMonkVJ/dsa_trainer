#include <bits/stdc++.h>
#include <cstddef>
using namespace std;

struct Node {
  int value;
  Node *next;
  Node *bottom;
};

Node *merge(Node *A, Node *B) {
  Node *currA = A;
  Node *currB = B;
  Node *head = nullptr;
  Node *newCurr = nullptr;
  if (A->value <= B->value) {
    newCurr = A;
    head = A;
    currA = A->bottom;
  } else {
    newCurr = B;
    head = B;
    currB = B->bottom;
  }
  newCurr->next = nullptr;

  while (currA != nullptr && currB != nullptr) {
    if (currA->value <= currB->value) {
      newCurr->bottom = currA;
      currA = currA->bottom;
    } else {
      newCurr->bottom = currB;
      currB = currB->bottom;
    }
    newCurr = newCurr->bottom;
    newCurr->next = nullptr;
  }

  while (currA != nullptr) {
    newCurr->bottom = currA;
    currA = currA->bottom;
    newCurr = newCurr->bottom;
    newCurr->next = nullptr;
  }

  while (currB != nullptr) {
    newCurr->bottom = currB;
    currB = currB->bottom;
    newCurr = newCurr->bottom;
    newCurr->next = nullptr;
  }

  return head;
}

Node *flatten(Node *head) {
  Node *curr = head;
  while (curr != nullptr && curr->next != nullptr) {
    Node *newNext = curr->next->next;
    curr = merge(curr, curr->next);
    curr->next = newNext;
  }

  return curr;
}

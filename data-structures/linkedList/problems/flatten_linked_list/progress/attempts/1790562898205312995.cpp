#include <bits/stdc++.h>
using namespace std;

struct Node {
  int value;
  Node *next;
  Node *bottom;
};

Node *merge(Node *A, Node *B) {
  Node *curr = nullptr;
  Node *head = nullptr;

  if (A->value > B->value) {
    curr = B;
    head = B;
    B = B->bottom;
  } else {
    curr = A;
    head = A;
    A = A->bottom;
  }

  while (A != nullptr && B != nullptr) {
    if (A->value > B->value) {
      curr->bottom = B;
      B = B->bottom;
    } else {
      curr->bottom = A;
      A = A->bottom;
    }
    curr = curr->bottom;
  }
  while (A != nullptr) {
    curr->bottom = A;
    A = A->bottom;
    curr = curr->bottom;
  }
  while (B != nullptr) {
    curr->bottom = B;
    B = B->bottom;
    curr = curr->bottom;
  }

  return head;
}

Node *flatten(Node *root) {
  if (root == nullptr)
    return nullptr;

  Node *curr = root;
  while (curr != nullptr && curr->next != nullptr) {
    Node *newNext = curr->next->next;
    Node *B = curr->next;
    Node *A = curr;
    A->next = nullptr;
    B->next = nullptr;
    Node *newHead = merge(A, B);
    curr = newHead;
    curr->next = newNext;
  }

  return curr;
}

#include <bits/stdc++.h>
using namespace std;

struct Node {
  int value;
  Node* next;
  explicit Node(int value = 0) : value(value), next(nullptr) {}
};

Node* reverseKGroup(Node* head, int k) {
  if (head == nullptr || k <= 1) return head;
  Node dummy(0); dummy.next = head;
  Node* groupPrev = &dummy;
  while (true) {
    Node* kth = groupPrev;
    for (int i = 0; i < k && kth != nullptr; ++i) kth = kth->next;
    if (kth == nullptr) break;
    Node* groupNext = kth->next;
    Node* prev = groupNext;
    Node* curr = groupPrev->next;
    while (curr != groupNext) {
      Node* next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }
    Node* oldFirst = groupPrev->next;
    groupPrev->next = kth;
    groupPrev = oldFirst;
  }
  return dummy.next;
}

int main() { return 0; }

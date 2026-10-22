#include <bits/stdc++.h>
using namespace std;

struct Node {
  int value;
  Node *next;
  Node *random;
};

Node *copyRandomList(Node *head) {
  if (head == nullptr)
    return nullptr;
  Node *curr = head;
  while (curr != nullptr) {
    Node *dup = new Node{curr->value, nullptr, nullptr};
    if (dup == nullptr)
      return nullptr;
    dup->value = curr->value;
    Node *next = curr->next;
    curr->next = dup;
    dup->next = next;
    curr = next;
  }
  curr = head;
  while (curr != nullptr) {
    Node *dup = curr->next;
    dup->random = curr->random ? curr->random->next : nullptr;
    curr = dup->next;
  }

  Node *ans = head->next;
  curr = head;
  while (curr != nullptr) {
    Node *dup = curr->next;
    Node *nextOriginal = dup->next;

    curr->next = nextOriginal;

    if (nextOriginal != nullptr)
      dup->next = nextOriginal->next;
    else
      dup->next = nullptr;

    curr = nextOriginal;
  }

  return ans;
}

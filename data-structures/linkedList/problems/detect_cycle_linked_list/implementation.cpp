#include <bits/stdc++.h>
using namespace std;

struct Node {
  int value;
  Node* next;
  explicit Node(int value = 0) : value(value), next(nullptr) {}
};

Node* detectCycle(Node* head) {
  Node* slow = head;
  Node* fast = head;
  while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) {
      slow = head;
      while (slow != fast) { slow = slow->next; fast = fast->next; }
      return slow;
    }
  }
  return nullptr;
}

int main() { return 0; }

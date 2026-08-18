#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int value = 0, ListNode* nextNode = nullptr) : val(value), next(nextNode) {}
};

void deleteNode(ListNode* node) {
  if (node == nullptr || node->next == nullptr) return;
  ListNode* successor = node->next;
  node->val = successor->val;
  node->next = successor->next;
  delete successor;
}

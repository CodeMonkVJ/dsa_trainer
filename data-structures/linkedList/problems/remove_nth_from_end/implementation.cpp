#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int value = 0, ListNode* nextNode = nullptr) : val(value), next(nextNode) {}
};

ListNode* removeNthFromEnd(ListNode* head, int n) {
  if (head == nullptr || n <= 0) return head;
  ListNode dummy(0, head);
  ListNode* fast = &dummy;
  for (int i = 0; i < n; ++i) {
    fast = fast->next;
    if (fast == nullptr) return head;
  }
  ListNode* slow = &dummy;
  while (fast->next != nullptr) {
    fast = fast->next;
    slow = slow->next;
  }
  ListNode* removed = slow->next;
  slow->next = removed->next;
  delete removed;
  return dummy.next;
}

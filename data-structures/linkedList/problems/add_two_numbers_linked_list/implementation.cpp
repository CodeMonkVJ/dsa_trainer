#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int value = 0, ListNode* nextNode = nullptr) : val(value), next(nextNode) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
  ListNode dummy;
  ListNode* tail = &dummy;
  int carry = 0;
  while (l1 != nullptr || l2 != nullptr || carry != 0) {
    int sum = carry;
    if (l1) { sum += l1->val; l1 = l1->next; }
    if (l2) { sum += l2->val; l2 = l2->next; }
    tail->next = new ListNode(sum % 10);
    tail = tail->next;
    carry = sum / 10;
  }
  if (dummy.next == nullptr) dummy.next = new ListNode(0);
  return dummy.next;
}

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  explicit ListNode(int value) : val(value), next(nullptr) {}
};

ListNode *rotateRight(ListNode *head, int k) {
  if (k <= 0 || head == nullptr || head->next == nullptr)
    return head;

  ListNode *tail = head;
  ListNode *prevTail = nullptr;
  int len = 0;

  while (tail != nullptr) {
    tail = tail->next;
    len++;
  }

  k = k % len;

  if (k == 0)
    return head;

  tail = head;

  while (tail != nullptr && k--) {
    prevTail = tail;
    tail = tail->next;
  }

  ListNode *target = head;
  ListNode *prevTarget = nullptr;
  while (tail != nullptr) {
    prevTail = tail;
    prevTarget = target;
    tail = tail->next;
    target = target->next;
  }

  prevTarget->next = nullptr;
  prevTail->next = head;
  head = target;

  return head;
}

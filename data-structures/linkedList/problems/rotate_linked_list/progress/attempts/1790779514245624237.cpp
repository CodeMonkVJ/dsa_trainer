#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  explicit ListNode(int value) : val(value), next(nullptr) {}
};

ListNode *rotateRight(ListNode *head, int k) {
  int n = 0;
  ListNode *curr = head;
  while (curr != nullptr) {
    n++;
    curr = curr->next;
  }

  if (n <= 1)
    return head;

  k = k % n;
  if (k <= 0)
    return head;

  int tailIndex = n - k - 1;
  ListNode *tail = head;
  while (tailIndex--)
    tail = tail->next;

  ListNode *newHead = tail->next;
  curr = newHead;

  while (curr->next != nullptr)
    curr = curr->next;

  curr->next = head;
  tail->next = nullptr;

  return newHead;
}

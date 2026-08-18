#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  explicit ListNode(int value) : val(value), next(nullptr) {}
};

ListNode* rotateRight(ListNode* head, int k) {
  if (!head || !head->next || k <= 0) return head;
  int length = 1;
  ListNode* tail = head;
  while (tail->next) { tail = tail->next; ++length; }
  k %= length;
  if (k == 0) return head;
  tail->next = head;
  int stepsToNewTail = length - k - 1;
  ListNode* newTail = head;
  while (stepsToNewTail-- > 0) newTail = newTail->next;
  ListNode* newHead = newTail->next;
  newTail->next = nullptr;
  return newHead;
}

int main() {
  ListNode a(1), b(2), c(3), d(4), e(5);
  a.next = &b; b.next = &c; c.next = &d; d.next = &e;
  cout << rotateRight(&a, 2)->val << '\n';
  return 0;
}

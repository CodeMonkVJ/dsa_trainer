#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int value;
  ListNode* next;
};

ListNode* mergeTwoSortedLists(ListNode* left, ListNode* right) {
  ListNode dummy{0, nullptr};
  ListNode* tail = &dummy;
  while (left != nullptr && right != nullptr) {
    if (left->value <= right->value) {
      tail->next = left;
      left = left->next;
    } else {
      tail->next = right;
      right = right->next;
    }
    tail = tail->next;
  }
  tail->next = left != nullptr ? left : right;
  return dummy.next;
}

ListNode* makeList(const vector<int>& values) {
  ListNode* head = nullptr;
  ListNode* tail = nullptr;
  for (int value : values) {
    ListNode* node = new ListNode{value, nullptr};
    if (head == nullptr) head = node;
    else tail->next = node;
    tail = node;
  }
  return head;
}

void freeList(ListNode* head) {
  while (head != nullptr) {
    ListNode* next = head->next;
    delete head;
    head = next;
  }
}

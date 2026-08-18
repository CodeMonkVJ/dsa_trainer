#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int value;
  ListNode* next;
};

ListNode* middleNode(ListNode* head) {
  ListNode* slow = head;
  ListNode* fast = head;
  while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
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

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int value;
  ListNode* next;
};

ListNode* reverseList(ListNode* head) {
  ListNode* previous = nullptr;
  ListNode* current = head;
  while (current != nullptr) {
    ListNode* next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }
  return previous;
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

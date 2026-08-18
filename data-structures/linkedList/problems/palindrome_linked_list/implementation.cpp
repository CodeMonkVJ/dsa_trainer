#include <bits/stdc++.h>
using namespace std;
struct ListNode { int value; ListNode* next; };

bool isPalindrome(ListNode* head) {
  if (!head || !head->next) return true;
  ListNode *slow = head, *fast = head;
  while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
  ListNode* second = slow;
  if (!fast) { // even length: slow is the first node of the second half
    second = slow;
  } else { // odd length: skip the middle node
    second = slow->next;
  }
  ListNode* prev = nullptr;
  for (ListNode* p = second; p; ) { ListNode* next = p->next; p->next = prev; prev = p; p = next; }
  ListNode* reversed = prev;
  bool result = true;
  for (ListNode *a = head, *b = reversed; b; a = a->next, b = b->next)
    if (a->value != b->value) { result = false; break; }
  for (ListNode* p = reversed, *tail = nullptr; p; ) { ListNode* next = p->next; p->next = tail; tail = p; p = next; }
  return result;
}

ListNode* makeList(const vector<int>& values) { ListNode* h=nullptr; ListNode* t=nullptr; for(int v:values){auto*n=new ListNode{v,nullptr}; if(!h)h=n;else t->next=n;t=n;} return h; }
void freeList(ListNode* head) { while(head){auto*n=head->next;delete head;head=n;} }

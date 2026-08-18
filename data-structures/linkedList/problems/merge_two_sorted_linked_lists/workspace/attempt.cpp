#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int value;
  ListNode *next;
};
ListNode *mergeTwoSortedLists(ListNode *left, ListNode *right) {
  return left != nullptr ? left : right;
}
ListNode *makeList(const vector<int> &) { return nullptr; }
void freeList(ListNode *) {}

#include <bits/stdc++.h>
using namespace std;

struct Node {
  int value;
  Node *next;
  explicit Node(int value = 0) : value(value), next(nullptr) {}
};

static Node *getNextGroup(Node *start, int k) {
  Node *curr = start;
  while (k-- > 0 && curr != nullptr) {
    curr = curr->next;
  }
  return curr;
}

static void reverseGroup(Node *&prevGroupTail, Node *&groupStart,
                         Node *&nextGroup) {
  Node *prev = nextGroup;
  Node *curr = groupStart;
  while (curr != nextGroup) {
    Node *next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  prevGroupTail->next = prev;
}

Node *reverseKGroup(Node *head, int k) {
  if (k <= 1)
    return head;
  Node dummy(-1);
  dummy.next = head;
  Node *prevGroupTail = &dummy;
  Node *groupStart = head;

  while (groupStart != nullptr) {
    Node *nextGroup = getNextGroup(groupStart, k);
    Node *check = groupStart;
    int count = 0;
    while (check != nullptr && count < k) {
      check = check->next;
      count++;
    }
    if (count < k)
      break;
    reverseGroup(prevGroupTail, groupStart, nextGroup);

    prevGroupTail = groupStart;
    groupStart = nextGroup;
  }
  return dummy.next;
}

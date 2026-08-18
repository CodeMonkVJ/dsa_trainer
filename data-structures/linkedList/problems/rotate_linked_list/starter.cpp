#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  explicit ListNode(int value) : val(value), next(nullptr) {}
};

ListNode *rotateRight(ListNode *head, int k) { return head; }

int main() {
  ListNode a(1), b(2), c(3), d(4), e(5);
  a.next = &b;
  b.next = &c;
  c.next = &d;
  d.next = &e;
  cout << rotateRight(&a, 2)->val << '\n';
}

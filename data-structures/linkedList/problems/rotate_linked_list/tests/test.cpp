#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(bool ok, const char *name) {
  ++total;

  if (ok)
    ++passed;

  cout << (ok ? "PASS " : "FAIL ") << name << '\n';

  string input = string("{\"test\":\"") + name + "\"}";

  dsa_test::emit_case(
      input,
      "true",
      ok ? "true" : "false",
      ok);
}

vector<int> values(ListNode *head) {
  vector<int> result;

  // Safety limit prevents a buggy circular list from hanging the test.
  for (int i = 0; head != nullptr && i < 1000; ++i) {
    result.push_back(head->val);
    head = head->next;
  }

  return result;
}

bool nullTerminated(ListNode *head, int expectedSize) {
  ListNode *curr = head;

  for (int i = 0; i < expectedSize && curr != nullptr; ++i)
    curr = curr->next;

  return curr == nullptr;
}

int main() {
  // Basic rotation.
  {
    ListNode a(1), b(2), c(3), d(4), e(5);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;

    ListNode *head = rotateRight(&a, 2);

    check(
        values(head) == vector<int>({4, 5, 1, 2, 3}) &&
            nullTerminated(head, 5),
        "rotates right by two");
  }

  // Rotation by one.
  {
    ListNode a(1), b(2), c(3), d(4);
    a.next = &b;
    b.next = &c;
    c.next = &d;

    ListNode *head = rotateRight(&a, 1);

    check(
        values(head) == vector<int>({4, 1, 2, 3}) &&
            nullTerminated(head, 4),
        "rotates right by one");
  }

  // Rotation by length should be unchanged.
  {
    ListNode a(1), b(2), c(3), d(4);
    a.next = &b;
    b.next = &c;
    c.next = &d;

    ListNode *head = rotateRight(&a, 4);

    check(
        values(head) == vector<int>({1, 2, 3, 4}) &&
            nullTerminated(head, 4),
        "rotation by list length");
  }

  // Rotation larger than length.
  {
    ListNode a(1), b(2), c(3);
    a.next = &b;
    b.next = &c;

    ListNode *head = rotateRight(&a, 8);

    check(
        values(head) == vector<int>({2, 3, 1}) &&
            nullTerminated(head, 3),
        "reduces large rotations");
  }

  // k much larger than length.
  {
    ListNode a(1), b(2), c(3), d(4), e(5);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;

    ListNode *head = rotateRight(&a, 102);

    check(
        values(head) == vector<int>({4, 5, 1, 2, 3}) &&
            nullTerminated(head, 5),
        "very large rotation");
  }

  // Zero rotation.
  {
    ListNode a(1), b(2), c(3);
    a.next = &b;
    b.next = &c;

    ListNode *head = rotateRight(&a, 0);

    check(
        head == &a &&
            values(head) == vector<int>({1, 2, 3}) &&
            nullTerminated(head, 3),
        "zero rotation");
  }

  // Negative k.
  {
    ListNode a(1), b(2), c(3);
    a.next = &b;
    b.next = &c;

    ListNode *head = rotateRight(&a, -3);

    check(
        head == &a &&
            values(head) == vector<int>({1, 2, 3}) &&
            nullTerminated(head, 3),
        "negative rotation");
  }

  // Empty list.
  {
    ListNode *head = rotateRight(nullptr, 5);

    check(
        head == nullptr,
        "empty list");
  }

  // Single node.
  {
    ListNode a(7);

    ListNode *head = rotateRight(&a, 100);

    check(
        head == &a &&
            a.next == nullptr &&
            values(head) == vector<int>({7}),
        "single node");
  }

  // Two-node list, rotation by one.
  {
    ListNode a(1), b(2);
    a.next = &b;

    ListNode *head = rotateRight(&a, 1);

    check(
        head == &b &&
            values(head) == vector<int>({2, 1}) &&
            head->next == &a &&
            a.next == nullptr,
        "two nodes");
  }

  // Rotate by length + one.
  {
    ListNode a(1), b(2), c(3), d(4);
    a.next = &b;
    b.next = &c;
    c.next = &d;

    ListNode *head = rotateRight(&a, 5);

    check(
        values(head) == vector<int>({4, 1, 2, 3}) &&
            nullTerminated(head, 4),
        "length plus one");
  }

  // Rotation must reuse the existing nodes.
  {
    ListNode a(1), b(2), c(3);
    a.next = &b;
    b.next = &c;

    ListNode *head = rotateRight(&a, 1);

    check(
        head == &c &&
            head->next == &a &&
            head->next->next == &b &&
            head->next->next->next == nullptr,
        "reuses existing nodes");
  }

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
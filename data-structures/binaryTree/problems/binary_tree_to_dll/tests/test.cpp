
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

  string input = string("{\"case\":\"") + name + "\"}";
  dsa_test::emit_case(
      input,
      "true",
      ok ? "true" : "false",
      ok);
}

vector<int> forwardValues(Node *head) {
  vector<int> result;

  while (head != nullptr) {
    result.push_back(head->data);  // data, not val
    head = head->right;
  }

  return result;
}

vector<int> backwardValues(Node *tail) {
  vector<int> result;

  while (tail != nullptr) {
    result.push_back(tail->data);  // data, not val
    tail = tail->left;
  }

  return result;
}

Node *getTail(Node *head) {
  if (head == nullptr)
    return nullptr;

  while (head->right != nullptr)
    head = head->right;

  return head;
}

int main() {
  // Empty tree.
  {
    Node *head = treeToDoublyList(nullptr);

    check(head == nullptr,
          "empty tree");
  }

  // Single node.
  {
    Node a(5);

    Node *head = treeToDoublyList(&a);

    check(head == &a &&
              a.left == nullptr &&
              a.right == nullptr,
          "single node");
  }

  // Simple balanced tree.
  //
  //     2
  //    / \
  //   1   3
  {
    Node n1(1), n2(2), n3(3);

    n2.left = &n1;
    n2.right = &n3;

    Node *head = treeToDoublyList(&n2);
    Node *tail = getTail(head);

    check(
        head == &n1 &&
            tail == &n3 &&
            head->left == nullptr &&
            tail->right == nullptr &&
            forwardValues(head) == vector<int>({1, 2, 3}) &&
            backwardValues(tail) == vector<int>({3, 2, 1}),
        "balanced three node tree");
  }

  // Left-skewed tree.
  //
  //       4
  //      /
  //     3
  //    /
  //   2
  //  /
  // 1
  {
    Node n1(1), n2(2), n3(3), n4(4);

    n4.left = &n3;
    n3.left = &n2;
    n2.left = &n1;

    Node *head = treeToDoublyList(&n4);
    Node *tail = getTail(head);

    check(
        head == &n1 &&
            tail == &n4 &&
            forwardValues(head) == vector<int>({1, 2, 3, 4}) &&
            backwardValues(tail) == vector<int>({4, 3, 2, 1}),
        "left skewed tree");
  }

  // Right-skewed tree.
  //
  // 1
  //  \
  //   2
  //    \
  //     3
  //      \
  //       4
  {
    Node n1(1), n2(2), n3(3), n4(4);

    n1.right = &n2;
    n2.right = &n3;
    n3.right = &n4;

    Node *head = treeToDoublyList(&n1);
    Node *tail = getTail(head);

    check(
        head == &n1 &&
            tail == &n4 &&
            forwardValues(head) == vector<int>({1, 2, 3, 4}) &&
            backwardValues(tail) == vector<int>({4, 3, 2, 1}),
        "right skewed tree");
  }

  // Larger tree.
  //
  //          4
  //        /   \
  //       2     6
  //      / \   / \
  //     1   3 5   7
  {
    Node n1(1), n2(2), n3(3), n4(4);
    Node n5(5), n6(6), n7(7);

    n4.left = &n2;
    n4.right = &n6;

    n2.left = &n1;
    n2.right = &n3;

    n6.left = &n5;
    n6.right = &n7;

    Node *head = treeToDoublyList(&n4);
    Node *tail = getTail(head);

    check(
        head == &n1 &&
            tail == &n7 &&
            head->left == nullptr &&
            tail->right == nullptr &&
            forwardValues(head) ==
                vector<int>({1, 2, 3, 4, 5, 6, 7}) &&
            backwardValues(tail) ==
                vector<int>({7, 6, 5, 4, 3, 2, 1}),
        "larger balanced tree");
  }

  // Verify original nodes are reused.
  {
    Node n1(1), n2(2), n3(3);

    n2.left = &n1;
    n2.right = &n3;

    Node *head = treeToDoublyList(&n2);

    check(
        head == &n1 &&
            head->right == &n2 &&
            n2.right == &n3,
        "reuses original nodes");
  }

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
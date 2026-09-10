#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

void check(bool ok, const char *name) {
  ++total;
  if (ok)
    ++passed;

  cout << (ok ? "PASS " : "FAIL ") << name << '\n';

  string input = string("{\"test\":\"") + name + "\"}";
  dsa_test::emit_case(input, ok ? "true" : "false",
                      ok ? "true" : "false", ok);
}

vector<int> values(Node *head, size_t limit = 1000) {
  vector<int> out;

  while (head != nullptr && out.size() < limit) {
    out.push_back(head->value);
    head = head->next;
  }

  return out;
}

Node *makeList(const vector<int> &input,
               vector<unique_ptr<Node>> &storage) {
  Node *head = nullptr;
  Node *tail = nullptr;

  for (int value : input) {
    storage.push_back(make_unique<Node>(value));
    Node *node = storage.back().get();

    if (head == nullptr)
      head = node;
    else
      tail->next = node;

    tail = node;
  }

  return head;
}

bool terminates(Node *head, size_t expectedNodes) {
  size_t count = 0;

  while (head != nullptr && count <= expectedNodes) {
    head = head->next;
    ++count;
  }

  return head == nullptr && count <= expectedNodes;
}

int main() {
  {
    vector<unique_ptr<Node>> storage;
    Node *head = makeList({1, 2, 3, 4, 5}, storage);

    Node *result = reverseKGroup(head, 2);

    check(
        values(result) == vector<int>({2, 1, 4, 3, 5}) &&
            terminates(result, 5),
        "multiple groups with leftover");
  }

  {
    vector<unique_ptr<Node>> storage;
    Node *head = makeList({1, 2, 3, 4, 5, 6}, storage);

    Node *result = reverseKGroup(head, 3);

    check(
        values(result) == vector<int>({3, 2, 1, 6, 5, 4}) &&
            terminates(result, 6),
        "exact groups");
  }

  {
    vector<unique_ptr<Node>> storage;
    Node *head = makeList({1, 2, 3}, storage);

    Node *result = reverseKGroup(head, 5);

    check(
        result == head &&
            values(result) == vector<int>({1, 2, 3}) &&
            terminates(result, 3),
        "k larger than list");
  }

  {
    vector<unique_ptr<Node>> storage;
    Node *head = makeList({1, 2, 3}, storage);

    Node *result = reverseKGroup(head, 3);

    check(
        values(result) == vector<int>({3, 2, 1}) &&
            terminates(result, 3),
        "k equals list length");
  }

  {
    vector<unique_ptr<Node>> storage;
    Node *head = makeList({1, 2, 3, 4}, storage);

    Node *result = reverseKGroup(head, 4);

    check(
        values(result) == vector<int>({4, 3, 2, 1}) &&
            terminates(result, 4),
        "reverse entire list");
  }

  {
    vector<unique_ptr<Node>> storage;
    Node *head = makeList({1}, storage);

    Node *result = reverseKGroup(head, 2);

    check(
        result == head &&
            values(result) == vector<int>({1}),
        "single node k larger");
  }

  {
    vector<unique_ptr<Node>> storage;
    Node *head = makeList({1}, storage);

    Node *result = reverseKGroup(head, 1);

    check(
        result == head &&
            values(result) == vector<int>({1}),
        "single node k one");
  }

  {
    vector<unique_ptr<Node>> storage;
    Node *head = makeList({1, 2, 3}, storage);

    check(
        reverseKGroup(head, 1) == head &&
            values(head) == vector<int>({1, 2, 3}),
        "k one no op");
  }

  {
    vector<unique_ptr<Node>> storage;
    Node *head = makeList({1, 2, 3}, storage);

    check(
        reverseKGroup(head, 0) == head &&
            values(head) == vector<int>({1, 2, 3}),
        "k zero no op");
  }

  {
    vector<unique_ptr<Node>> storage;
    Node *head = makeList({1, 2, 3}, storage);

    check(
        reverseKGroup(head, -4) == head &&
            values(head) == vector<int>({1, 2, 3}),
        "negative k no op");
  }

  check(
      reverseKGroup(nullptr, 3) == nullptr,
      "empty list");

  {
    vector<unique_ptr<Node>> storage;
    Node *head = makeList({1, 2, 3, 4, 5, 6, 7}, storage);

    Node *result = reverseKGroup(head, 3);

    check(
        values(result) ==
                vector<int>({3, 2, 1, 6, 5, 4, 7}) &&
            terminates(result, 7),
        "two full groups and one leftover");
  }

  {
    vector<unique_ptr<Node>> storage;
    Node *head = makeList({1, 2, 3, 4, 5, 6, 7, 8}, storage);

    Node *result = reverseKGroup(head, 3);

    check(
        values(result) ==
                vector<int>({3, 2, 1, 6, 5, 4, 7, 8}) &&
            terminates(result, 8),
        "leftover group of two");
  }

  {
    vector<unique_ptr<Node>> storage;
    Node *head = makeList({1, 2, 3, 4, 5}, storage);

    Node *result = reverseKGroup(head, 4);

    check(
        values(result) == vector<int>({4, 3, 2, 1, 5}) &&
            terminates(result, 5),
        "one full group one leftover");
  }

  {
    vector<unique_ptr<Node>> storage;
    Node *head = makeList({1, 2, 3, 4, 5, 6, 7, 8}, storage);

    Node *result = reverseKGroup(head, 2);

    check(
        values(result) ==
                vector<int>({2, 1, 4, 3, 6, 5, 8, 7}) &&
            terminates(result, 8),
        "many groups of two");
  }

  {
    vector<unique_ptr<Node>> storage;
    Node *head = makeList({5, 5, 5, 5, 5}, storage);

    Node *result = reverseKGroup(head, 2);

    check(
        values(result) ==
                vector<int>({5, 5, 5, 5, 5}) &&
            terminates(result, 5),
        "duplicate values");
  }

  {
    vector<unique_ptr<Node>> storage;
    Node *head =
        makeList({-3, -2, -1, 0, 1, 2}, storage);

    Node *result = reverseKGroup(head, 3);

    check(
        values(result) ==
                vector<int>({-1, -2, -3, 2, 1, 0}) &&
            terminates(result, 6),
        "negative and positive values");
  }

  {
    vector<unique_ptr<Node>> storage;
    vector<int> large(101);
    iota(large.begin(), large.end(), 0);

    Node *head = makeList(large, storage);
    Node *result = reverseKGroup(head, 10);

    vector<int> expected;

    for (int start = 0; start < 100; start += 10) {
      for (int i = start + 9; i >= start; --i)
        expected.push_back(i);
    }

    expected.push_back(100);

    check(
        values(result, 200) == expected &&
            terminates(result, 101),
        "large input with short tail");
  }

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
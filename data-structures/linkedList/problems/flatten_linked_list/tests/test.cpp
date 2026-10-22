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
  dsa_test::emit_case(
      input,
      "true",
      ok ? "true" : "false",
      ok);
}

Node *n(int value) {
  return new Node{value, nullptr, nullptr};
}

vector<int> readValues(Node *head, bool &structureOk) {
  vector<int> values;
  unordered_set<Node *> seen;

  while (head) {
    // Detect cycle / repeated node.
    if (seen.count(head)) {
      structureOk = false;
      break;
    }

    seen.insert(head);

    // Final flattened structure must use bottom only.
    if (head->next != nullptr)
      structureOk = false;

    values.push_back(head->value);
    head = head->bottom;
  }

  return values;
}

bool usesExactlyNodes(Node *head, const vector<Node *> &original) {
  unordered_set<Node *> expected(original.begin(), original.end());
  unordered_set<Node *> seen;

  for (Node *p = head; p; p = p->bottom) {
    if (seen.count(p))
      return false;

    seen.insert(p);

    if (!expected.count(p))
      return false;
  }

  return seen.size() == expected.size();
}

void destroyFlattened(Node *head) {
  unordered_set<Node *> seen;

  while (head && !seen.count(head)) {
    seen.insert(head);

    Node *next = head->bottom;
    delete head;
    head = next;
  }
}

int main() {
  // Empty.
  check(
      flatten(nullptr) == nullptr,
      "empty");

  // Single node.
  {
    Node *a = n(5);

    Node *out = flatten(a);

    bool structureOk = true;

    check(
        readValues(out, structureOk) == vector<int>({5}) &&
            structureOk &&
            out == a,
        "single node");

    destroyFlattened(out);
  }

  // One vertical list only.
  {
    Node *a = n(1);
    Node *b = n(3);
    Node *c = n(7);
    Node *d = n(10);

    a->bottom = b;
    b->bottom = c;
    c->bottom = d;

    vector<Node *> original{a, b, c, d};

    Node *out = flatten(a);

    bool structureOk = true;

    check(
        readValues(out, structureOk) ==
                vector<int>({1, 3, 7, 10}) &&
            structureOk &&
            usesExactlyNodes(out, original),
        "single vertical list");

    destroyFlattened(out);
  }

  // Basic two-column merge.
  {
    Node *a = n(1);
    Node *b = n(4);
    Node *c = n(2);
    Node *d = n(3);

    a->bottom = b;

    c->bottom = d;

    a->next = c;

    vector<Node *> original{a, b, c, d};

    Node *out = flatten(a);

    bool structureOk = true;

    check(
        readValues(out, structureOk) ==
                vector<int>({1, 2, 3, 4}) &&
            structureOk &&
            usesExactlyNodes(out, original),
        "merges two sorted columns");

    destroyFlattened(out);
  }

  // One column entirely before another.
  {
    Node *a = n(1);
    Node *b = n(2);
    Node *c = n(3);

    Node *d = n(10);
    Node *e = n(20);

    a->bottom = b;
    b->bottom = c;

    d->bottom = e;

    a->next = d;

    vector<Node *> original{a, b, c, d, e};

    Node *out = flatten(a);

    bool structureOk = true;

    check(
        readValues(out, structureOk) ==
                vector<int>({1, 2, 3, 10, 20}) &&
            structureOk &&
            usesExactlyNodes(out, original),
        "non interleaving columns");

    destroyFlattened(out);
  }

  // Strong interleaving.
  {
    Node *a = n(1);
    Node *b = n(4);
    Node *c = n(7);
    Node *d = n(10);

    Node *e = n(2);
    Node *f = n(5);
    Node *g = n(8);
    Node *h = n(11);

    Node *i = n(3);
    Node *j = n(6);
    Node *k = n(9);
    Node *l = n(12);

    a->bottom = b;
    b->bottom = c;
    c->bottom = d;

    e->bottom = f;
    f->bottom = g;
    g->bottom = h;

    i->bottom = j;
    j->bottom = k;
    k->bottom = l;

    a->next = e;
    e->next = i;

    vector<Node *> original{
        a, b, c, d,
        e, f, g, h,
        i, j, k, l};

    Node *out = flatten(a);

    bool structureOk = true;

    check(
        readValues(out, structureOk) ==
                vector<int>({
                    1, 2, 3, 4, 5, 6,
                    7, 8, 9, 10, 11, 12}) &&
            structureOk &&
            usesExactlyNodes(out, original),
        "heavily interleaved columns");

    destroyFlattened(out);
  }

  // Many horizontal heads, no bottom children.
  {
    Node *a = n(1);
    Node *b = n(2);
    Node *c = n(3);
    Node *d = n(4);
    Node *e = n(5);

    a->next = b;
    b->next = c;
    c->next = d;
    d->next = e;

    vector<Node *> original{a, b, c, d, e};

    Node *out = flatten(a);

    bool structureOk = true;

    check(
        readValues(out, structureOk) ==
                vector<int>({1, 2, 3, 4, 5}) &&
            structureOk &&
            usesExactlyNodes(out, original),
        "horizontal heads only");

    destroyFlattened(out);
  }

  // Duplicate values.
  {
    Node *a = n(1);
    Node *b = n(2);
    Node *c = n(2);

    Node *d = n(1);
    Node *e = n(2);
    Node *f = n(3);

    a->bottom = b;
    b->bottom = c;

    d->bottom = e;
    e->bottom = f;

    a->next = d;

    vector<Node *> original{a, b, c, d, e, f};

    Node *out = flatten(a);

    bool structureOk = true;

    check(
        readValues(out, structureOk) ==
                vector<int>({1, 1, 2, 2, 2, 3}) &&
            structureOk &&
            usesExactlyNodes(out, original),
        "duplicate values");

    destroyFlattened(out);
  }

  // Negative values.
  {
    Node *a = n(-10);
    Node *b = n(-3);
    Node *c = n(5);

    Node *d = n(-8);
    Node *e = n(0);
    Node *f = n(7);

    a->bottom = b;
    b->bottom = c;

    d->bottom = e;
    e->bottom = f;

    a->next = d;

    vector<Node *> original{a, b, c, d, e, f};

    Node *out = flatten(a);

    bool structureOk = true;

    check(
        readValues(out, structureOk) ==
                vector<int>({-10, -8, -3, 0, 5, 7}) &&
            structureOk &&
            usesExactlyNodes(out, original),
        "negative values");

    destroyFlattened(out);
  }

  // Uneven column lengths.
  {
    Node *a = n(1);
    Node *b = n(50);

    Node *c = n(2);
    Node *d = n(3);
    Node *e = n(4);
    Node *f = n(5);
    Node *g = n(6);

    Node *h = n(7);

    a->bottom = b;

    c->bottom = d;
    d->bottom = e;
    e->bottom = f;
    f->bottom = g;

    a->next = c;
    c->next = h;

    vector<Node *> original{a, b, c, d, e, f, g, h};

    Node *out = flatten(a);

    bool structureOk = true;

    check(
        readValues(out, structureOk) ==
                vector<int>({1, 2, 3, 4, 5, 6, 7, 50}) &&
            structureOk &&
            usesExactlyNodes(out, original),
        "uneven column lengths");

    destroyFlattened(out);
  }

  // Explicitly ensure original nodes are reused and no replacement
  // data nodes are introduced.
  {
    Node *a = n(1);
    Node *b = n(5);
    Node *c = n(2);
    Node *d = n(4);
    Node *e = n(3);

    a->bottom = b;

    c->bottom = d;

    a->next = c;
    c->next = e;

    vector<Node *> original{a, b, c, d, e};

    Node *out = flatten(a);

    check(
        usesExactlyNodes(out, original),
        "reuses every original node exactly once");

    destroyFlattened(out);
  }

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
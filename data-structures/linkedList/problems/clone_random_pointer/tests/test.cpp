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
      ok ? "true" : "false",
      ok ? "true" : "false",
      ok);
}

vector<Node *> collect(Node *head) {
  vector<Node *> out;

  for (Node *p = head; p; p = p->next)
    out.push_back(p);

  return out;
}

bool validateClone(
    const vector<Node *> &original,
    const vector<Node *> &clone) {

  if (original.size() != clone.size())
    return false;

  unordered_map<Node *, int> originalIndex;
  for (int i = 0; i < (int)original.size(); ++i)
    originalIndex[original[i]] = i;

  for (int i = 0; i < (int)original.size(); ++i) {
    if (original[i] == clone[i])
      return false;

    if (original[i]->value != clone[i]->value)
      return false;

    if (original[i]->random == nullptr) {
      if (clone[i]->random != nullptr)
        return false;
    } else {
      int target = originalIndex[original[i]->random];

      if (clone[i]->random != clone[target])
        return false;
    }
  }

  return true;
}

bool sharesAnyNode(Node *a, Node *b) {
  unordered_set<Node *> seen;

  for (Node *p = a; p; p = p->next)
    seen.insert(p);

  for (Node *p = b; p; p = p->next) {
    if (seen.count(p))
      return true;
  }

  return false;
}

bool cloneRandomPointsOnlyIntoClone(Node *clone) {
  unordered_set<Node *> nodes;

  for (Node *p = clone; p; p = p->next)
    nodes.insert(p);

  for (Node *p = clone; p; p = p->next) {
    if (p->random && !nodes.count(p->random))
      return false;
  }

  return true;
}

void destroy(Node *head) {
  while (head) {
    Node *next = head->next;
    delete head;
    head = next;
  }
}

int main() {
  // Empty list.
  check(
      copyRandomList(nullptr) == nullptr,
      "empty list");

  // Single node, null random.
  {
    Node *a = new Node{7, nullptr, nullptr};

    Node *c = copyRandomList(a);

    check(
        c != nullptr &&
        c != a &&
        c->value == 7 &&
        c->next == nullptr &&
        c->random == nullptr,
        "single node with null random");

    destroy(a);
    destroy(c);
  }

  // Single node, self random.
  {
    Node *a = new Node{42, nullptr, nullptr};
    a->random = a;

    Node *c = copyRandomList(a);

    check(
        c != nullptr &&
        c != a &&
        c->random == c,
        "single node self random");

    destroy(a);
    destroy(c);
  }

  // Classic mixed example.
  {
    vector<Node *> o;

    for (int v : {7, 13, 11, 10, 1})
      o.push_back(new Node{v, nullptr, nullptr});

    for (int i = 0; i + 1 < (int)o.size(); ++i)
      o[i]->next = o[i + 1];

    o[0]->random = nullptr;
    o[1]->random = o[0];
    o[2]->random = o[4];
    o[3]->random = o[2];
    o[4]->random = o[0];

    Node *c = copyRandomList(o[0]);

    vector<Node *> cl = collect(c);

    check(
        validateClone(o, cl),
        "classic random relationships");

    check(
        !sharesAnyNode(o[0], c),
        "classic clone shares no nodes");

    check(
        cloneRandomPointsOnlyIntoClone(c),
        "classic clone random pointers stay inside clone");

    destroy(o[0]);
    destroy(c);
  }

  // All random pointers null.
  {
    vector<Node *> o;

    for (int v : {1, 2, 3, 4})
      o.push_back(new Node{v, nullptr, nullptr});

    for (int i = 0; i + 1 < (int)o.size(); ++i)
      o[i]->next = o[i + 1];

    Node *c = copyRandomList(o[0]);

    check(
        validateClone(o, collect(c)),
        "all random pointers null");

    destroy(o[0]);
    destroy(c);
  }

  // Forward random links.
  {
    vector<Node *> o;

    for (int v : {1, 2, 3, 4})
      o.push_back(new Node{v, nullptr, nullptr});

    for (int i = 0; i + 1 < (int)o.size(); ++i)
      o[i]->next = o[i + 1];

    o[0]->random = o[3];
    o[1]->random = o[3];
    o[2]->random = o[3];
    o[3]->random = nullptr;

    Node *c = copyRandomList(o[0]);

    check(
        validateClone(o, collect(c)),
        "forward random links");

    destroy(o[0]);
    destroy(c);
  }

  // Backward random links.
  {
    vector<Node *> o;

    for (int v : {10, 20, 30, 40})
      o.push_back(new Node{v, nullptr, nullptr});

    for (int i = 0; i + 1 < (int)o.size(); ++i)
      o[i]->next = o[i + 1];

    o[0]->random = nullptr;
    o[1]->random = o[0];
    o[2]->random = o[1];
    o[3]->random = o[0];

    Node *c = copyRandomList(o[0]);

    check(
        validateClone(o, collect(c)),
        "backward random links");

    destroy(o[0]);
    destroy(c);
  }

  // Mixed self-random pointers.
  {
    vector<Node *> o;

    for (int v : {5, 6, 7})
      o.push_back(new Node{v, nullptr, nullptr});

    o[0]->next = o[1];
    o[1]->next = o[2];

    o[0]->random = o[0];
    o[1]->random = o[2];
    o[2]->random = o[2];

    Node *c = copyRandomList(o[0]);

    check(
        validateClone(o, collect(c)),
        "mixed self random pointers");

    destroy(o[0]);
    destroy(c);
  }

  // Duplicate values — relationships must be based on node identity.
  {
    vector<Node *> o;

    for (int v : {5, 5, 5, 5})
      o.push_back(new Node{v, nullptr, nullptr});

    for (int i = 0; i + 1 < (int)o.size(); ++i)
      o[i]->next = o[i + 1];

    o[0]->random = o[2];
    o[1]->random = o[0];
    o[2]->random = o[3];
    o[3]->random = o[1];

    Node *c = copyRandomList(o[0]);

    check(
        validateClone(o, collect(c)),
        "duplicate values preserve identity relationships");

    destroy(o[0]);
    destroy(c);
  }

  // Original next pointers must be restored.
  {
    vector<Node *> o;

    for (int v : {1, 2, 3, 4, 5})
      o.push_back(new Node{v, nullptr, nullptr});

    for (int i = 0; i + 1 < (int)o.size(); ++i)
      o[i]->next = o[i + 1];

    o[0]->random = o[4];
    o[1]->random = o[3];
    o[2]->random = o[2];
    o[3]->random = o[1];
    o[4]->random = o[0];

    vector<Node *> originalNext(o.size());

    for (int i = 0; i < (int)o.size(); ++i)
      originalNext[i] = o[i]->next;

    Node *c = copyRandomList(o[0]);

    bool restored = true;

    for (int i = 0; i < (int)o.size(); ++i)
      restored = restored && o[i]->next == originalNext[i];

    check(
        restored,
        "original next links restored");

    destroy(o[0]);
    destroy(c);
  }

  // Original random pointers must remain unchanged.
  {
    vector<Node *> o;

    for (int v : {8, 9, 10})
      o.push_back(new Node{v, nullptr, nullptr});

    o[0]->next = o[1];
    o[1]->next = o[2];

    o[0]->random = o[2];
    o[1]->random = o[0];
    o[2]->random = o[1];

    vector<Node *> originalRandom;

    for (Node *x : o)
      originalRandom.push_back(x->random);

    Node *c = copyRandomList(o[0]);

    bool unchanged = true;

    for (int i = 0; i < (int)o.size(); ++i)
      unchanged = unchanged &&
                  o[i]->random == originalRandom[i];

    check(
        unchanged,
        "original random links unchanged");

    destroy(o[0]);
    destroy(c);
  }

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
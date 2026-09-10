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

  cout << (ok ? "PASS " : "FAIL ")
       << name << '\n';

  string input = string("{\"test\":\"") + name + "\"}";

  dsa_test::emit_case(
      input,
      ok ? "true" : "false",
      ok ? "true" : "false",
      ok);
}

int main() {
  // Standard intersection in the middle.
  {
    Node shared1(8), shared2(10);
    Node a1(1), a2(3);
    Node b1(2), b2(4);

    shared1.next = &shared2;

    a1.next = &a2;
    a2.next = &shared1;

    b1.next = &b2;
    b2.next = &shared1;

    check(
        getIntersectionNode(&a1, &b1) == &shared1,
        "intersection in middle");
  }

  // Intersection is the final node.
  {
    Node tail(99);
    Node a1(1), a2(2);
    Node b1(3), b2(4), b3(5);

    a1.next = &a2;
    a2.next = &tail;

    b1.next = &b2;
    b2.next = &b3;
    b3.next = &tail;

    check(
        getIntersectionNode(&a1, &b1) == &tail,
        "intersection at tail");
  }

  // Same head.
  {
    Node n1(1), n2(2), n3(3);

    n1.next = &n2;
    n2.next = &n3;

    check(
        getIntersectionNode(&n1, &n1) == &n1,
        "same head");
  }

  // One list starts inside the other.
  {
    Node n1(1), n2(2), n3(3), n4(4);

    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;

    check(
        getIntersectionNode(&n1, &n3) == &n3,
        "one list contained in other");
  }

  // Unequal prefix lengths before intersection.
  {
    Node shared1(50), shared2(60);

    Node a1(1), a2(2), a3(3), a4(4);
    Node b1(9);

    shared1.next = &shared2;

    a1.next = &a2;
    a2.next = &a3;
    a3.next = &a4;
    a4.next = &shared1;

    b1.next = &shared1;

    check(
        getIntersectionNode(&a1, &b1) == &shared1,
        "unequal prefix lengths");
  }

  // Large length difference before shared tail.
  {
    Node shared(100);

    Node a1(1), a2(2), a3(3), a4(4), a5(5);
    Node b1(10);

    a1.next = &a2;
    a2.next = &a3;
    a3.next = &a4;
    a4.next = &a5;
    a5.next = &shared;

    b1.next = &shared;

    check(
        getIntersectionNode(&a1, &b1) == &shared,
        "large length difference");
  }

  // Completely disjoint lists.
  {
    Node a1(1), a2(2), a3(3);
    Node b1(4), b2(5), b3(6);

    a1.next = &a2;
    a2.next = &a3;

    b1.next = &b2;
    b2.next = &b3;

    check(
        getIntersectionNode(&a1, &b1) == nullptr,
        "disjoint lists");
  }

  // Same values but different node identities.
  {
    Node a1(1), a2(2), a3(3);
    Node b1(1), b2(2), b3(3);

    a1.next = &a2;
    a2.next = &a3;

    b1.next = &b2;
    b2.next = &b3;

    check(
        getIntersectionNode(&a1, &b1) == nullptr,
        "same values different nodes");
  }

  // Single-node lists, same node.
  {
    Node n(7);

    check(
        getIntersectionNode(&n, &n) == &n,
        "single shared node");
  }

  // Single-node lists, different nodes.
  {
    Node a(7), b(7);

    check(
        getIntersectionNode(&a, &b) == nullptr,
        "single disjoint nodes");
  }

  // One empty list.
  {
    Node n(7);

    check(
        getIntersectionNode(nullptr, &n) == nullptr &&
            getIntersectionNode(&n, nullptr) == nullptr,
        "one empty list");
  }

  // Both empty.
  check(
      getIntersectionNode(nullptr, nullptr) == nullptr,
      "both empty");

  // Intersection immediately after first node of one list.
  {
    Node shared1(20), shared2(30);
    Node a1(10);
    Node b1(1), b2(2), b3(3);

    shared1.next = &shared2;

    a1.next = &shared1;

    b1.next = &b2;
    b2.next = &b3;
    b3.next = &shared1;

    check(
        getIntersectionNode(&a1, &b1) == &shared1,
        "short prefix versus long prefix");
  }

  // Ensure the first shared node is returned,
  // not some later shared node.
  {
    Node shared1(7), shared2(8), shared3(9);
    Node a1(1);
    Node b1(2);

    shared1.next = &shared2;
    shared2.next = &shared3;

    a1.next = &shared1;
    b1.next = &shared1;

    check(
        getIntersectionNode(&a1, &b1) == &shared1,
        "returns first shared node");
  }

  // Verify input lists remain unchanged.
  {
    Node shared1(8), shared2(10);
    Node a1(1), a2(3);
    Node b1(2), b2(4);

    shared1.next = &shared2;

    a1.next = &a2;
    a2.next = &shared1;

    b1.next = &b2;
    b2.next = &shared1;

    Node *result = getIntersectionNode(&a1, &b1);

    check(
        result == &shared1 &&
            a1.next == &a2 &&
            a2.next == &shared1 &&
            b1.next == &b2 &&
            b2.next == &shared1 &&
            shared1.next == &shared2 &&
            shared2.next == nullptr,
        "lists remain unchanged");
  }

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
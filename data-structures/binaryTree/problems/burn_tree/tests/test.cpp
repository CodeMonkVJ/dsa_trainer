#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

void check(bool x, const char *n) {
  ++total;

  if (x)
    ++passed;

  string input = "{\"case\":\"" + string(n) + "\"}";
  dsa_test::emit_case(
      input,
      "true",
      x ? "true" : "false",
      x);
}

int main() {
  // Empty tree.
  check(
      burnTime(nullptr, 10) == -1,
      "empty tree");

  // Single node.
  {
    TreeNode x(8);

    check(
        burnTime(&x, 8) == 0,
        "single node target");

    check(
        burnTime(&x, 99) == -1,
        "single node missing target");
  }

  // Main irregular tree:
  //
  //          1
  //        /   \
  //       2     3
  //      / \     \
  //     4   5     6
  //                \
  //                 7
  {
    TreeNode a(1), b(2), c(3), d(4), e(5), f(6), g(7);

    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;
    f.right = &g;

    check(
        burnTime(&a, 5) == 5,
        "burn from leaf");

    check(
        burnTime(&a, 1) == 3,
        "burn from root");

    check(
        burnTime(&a, 2) == 4,
        "burn from internal node");

    check(
        burnTime(&a, 3) == 3,
        "burn from opposite internal node");

    check(
        burnTime(&a, 7) == 5,
        "burn from deepest leaf");

    check(
        burnTime(&a, 99) == -1,
        "missing target");
  }

  // Two-node tree.
  {
    TreeNode a(1), b(2);
    a.left = &b;

    check(
        burnTime(&a, 1) == 1,
        "two nodes from root");

    check(
        burnTime(&a, 2) == 1,
        "two nodes from child");
  }

  // Left-skewed tree:
  //
  // 1
  // |
  // 2
  // |
  // 3
  // |
  // 4
  // |
  // 5
  {
    TreeNode a(1), b(2), c(3), d(4), e(5);

    a.left = &b;
    b.left = &c;
    c.left = &d;
    d.left = &e;

    check(
        burnTime(&a, 1) == 4,
        "left skew from root");

    check(
        burnTime(&a, 5) == 4,
        "left skew from leaf");

    check(
        burnTime(&a, 3) == 2,
        "left skew from middle");
  }

  // Right-skewed tree.
  {
    TreeNode a(1), b(2), c(3), d(4);

    a.right = &b;
    b.right = &c;
    c.right = &d;

    check(
        burnTime(&a, 4) == 3,
        "right skew from leaf");

    check(
        burnTime(&a, 2) == 2,
        "right skew from internal");
  }

  // Balanced tree:
  //
  //        1
  //      /   \
  //     2     3
  //    / \   / \
  //   4   5 6   7
  {
    TreeNode a(1), b(2), c(3), d(4), e(5), f(6), g(7);

    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = &f;
    c.right = &g;

    check(
        burnTime(&a, 1) == 2,
        "balanced from root");

    check(
        burnTime(&a, 4) == 4,
        "balanced from leaf");

    check(
        burnTime(&a, 2) == 3,
        "balanced from internal node");
  }

  // Deeply unbalanced tree:
  //
  //       10
  //      /  \
  //     5    20
  //    /       \
  //   3         30
  //  /            \
  // 1              40
  //                  \
  //                   50
  {
    TreeNode a(10), b(5), c(20), d(3), e(30), f(1), g(40), h(50);

    a.left = &b;
    a.right = &c;

    b.left = &d;
    d.left = &f;

    c.right = &e;
    e.right = &g;
    g.right = &h;

    check(
        burnTime(&a, 1) == 7,
        "farthest node across root");

    check(
        burnTime(&a, 50) == 7,
        "deep opposite endpoint");

    check(
        burnTime(&a, 10) == 4,
        "unbalanced tree from root");
  }

  // Target is a leaf, but farthest node is not the root.
  //
  //       1
  //      / \
  //     2   3
  //        /
  //       4
  //      /
  //     5
  {
    TreeNode a(1), b(2), c(3), d(4), e(5);

    a.left = &b;
    a.right = &c;
    c.left = &d;
    d.left = &e;

    check(
        burnTime(&a, 2) == 4,
        "leaf target farthest below sibling subtree");
  }

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
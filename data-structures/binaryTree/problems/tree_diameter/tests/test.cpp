#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

void check(TreeNode *root, int expected, const char *name) {
  ++total;

  int actual = treeDiameter(root);
  bool ok = actual == expected;

  if (ok)
    ++passed;

  string input = "{\"case\":\"" + string(name) + "\"}";

  dsa_test::emit_case(
      input,
      to_string(expected),
      to_string(actual),
      ok);
}

int main() {
  // Empty tree.
  check(
      nullptr,
      0,
      "empty tree");

  // Single node.
  {
    TreeNode a(7);

    check(
        &a,
        0,
        "single node");
  }

  // Two nodes.
  //
  // 1
  //  \
  //   2
  {
    TreeNode a(1), b(2);
    a.right = &b;

    check(
        &a,
        1,
        "two nodes");
  }

  // Original example.
  //
  //        1
  //       / \
  //      2   3
  //     / \
  //    4   5
  //   /
  //  6
  //
  // Longest: 6-4-2-1-3 = 4 edges.
  {
    TreeNode a(1), b(2), c(3),
             d(4), e(5), f(6);

    a.left = &b;
    a.right = &c;

    b.left = &d;
    b.right = &e;

    d.left = &f;

    check(
        &a,
        4,
        "asymmetric tree");
  }

  // Balanced tree.
  //
  //        1
  //      /   \
  //     2     3
  //    / \   / \
  //   4   5 6   7
  //
  // Example longest: 4-2-1-3-6 = 4 edges.
  {
    TreeNode a(1), b(2), c(3),
             d(4), e(5), f(6), g(7);

    a.left = &b;
    a.right = &c;

    b.left = &d;
    b.right = &e;

    c.left = &f;
    c.right = &g;

    check(
        &a,
        4,
        "balanced tree");
  }

  // Left-skewed.
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
  //
  {
    TreeNode a(1), b(2), c(3), d(4), e(5);

    a.left = &b;
    b.left = &c;
    c.left = &d;
    d.left = &e;

    check(
        &a,
        4,
        "left skewed tree");
  }

  // Right-skewed.
  {
    TreeNode a(1), b(2), c(3), d(4), e(5);

    a.right = &b;
    b.right = &c;
    c.right = &d;
    d.right = &e;

    check(
        &a,
        4,
        "right skewed tree");
  }

  // Important case: diameter does NOT pass through root.
  //
  //          1
  //         /
  //        2
  //       / \
  //      3   4
  //     /     \
  //    5       6
  //   /         \
  //  7           8
  //
  // Longest:
  // 7-5-3-2-4-6-8
  //
  // = 6 edges.
  {
    TreeNode a(1), b(2), c(3), d(4),
             e(5), f(6), g(7), h(8);

    a.left = &b;

    b.left = &c;
    b.right = &d;

    c.left = &e;
    e.left = &g;

    d.right = &f;
    f.right = &h;

    check(
        &a,
        6,
        "diameter entirely inside subtree");
  }

  // Root has two very different subtree depths.
  //
  //        10
  //       /  \
  //      5    20
  //     /
  //    4
  //   /
  //  3
  // /
  // 2
  //
  // Longest: 2-3-4-5-10-20 = 5 edges.
  {
    TreeNode a(10), b(5), c(20),
             d(4), e(3), f(2);

    a.left = &b;
    a.right = &c;

    b.left = &d;
    d.left = &e;
    e.left = &f;

    check(
        &a,
        5,
        "deep one sided subtree");
  }

  // Diameter through an internal node with both branches.
  //
  //       1
  //      /
  //     2
  //    / \
  //   3   4
  //  /     \
  // 5       6
  //
  // Longest: 5-3-2-4-6 = 4 edges.
  {
    TreeNode a(1), b(2), c(3),
             d(4), e(5), f(6);

    a.left = &b;

    b.left = &c;
    b.right = &d;

    c.left = &e;
    d.right = &f;

    check(
        &a,
        4,
        "internal node gives diameter");
  }

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
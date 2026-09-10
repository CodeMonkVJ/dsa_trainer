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

  string input =
      string("{\"test\":\"") + name + "\"}";

  dsa_test::emit_case(
      input,
      "true",
      ok ? "true" : "false",
      ok);
}

int main() {
  // Empty tree.
  {
    check(
        isSymmetric(nullptr),
        "empty tree");
  }

  // Single node.
  {
    TreeNode root{1, nullptr, nullptr};

    check(
        isSymmetric(&root),
        "single node");
  }

  // Simple symmetric tree.
  //
  //       1
  //      / \
  //     2   2
  //    / \ / \
  //   3  4 4  3
  {
    TreeNode a{3, nullptr, nullptr};
    TreeNode b{4, nullptr, nullptr};
    TreeNode c{4, nullptr, nullptr};
    TreeNode d{3, nullptr, nullptr};

    TreeNode l{2, &a, &b};
    TreeNode r{2, &c, &d};

    TreeNode root{1, &l, &r};

    check(
        isSymmetric(&root),
        "symmetric full tree");
  }

  // Same values but wrong mirrored placement.
  //
  //       1
  //      / \
  //     2   2
  //    /     \
  //   3       3
  //
  // This is symmetric and should be true.
  {
    TreeNode a{3, nullptr, nullptr};
    TreeNode b{3, nullptr, nullptr};

    TreeNode l{2, &a, nullptr};
    TreeNode r{2, nullptr, &b};

    TreeNode root{1, &l, &r};

    check(
        isSymmetric(&root),
        "symmetric with mirrored children");
  }

  // Same structure but different values.
  {
    TreeNode a{3, nullptr, nullptr};
    TreeNode b{4, nullptr, nullptr};

    TreeNode l{2, &a, nullptr};
    TreeNode r{2, nullptr, &b};

    TreeNode root{1, &l, &r};

    check(
        !isSymmetric(&root),
        "different mirrored values");
  }

  // One side has an extra child.
  {
    TreeNode a{3, nullptr, nullptr};
    TreeNode b{3, nullptr, nullptr};
    TreeNode extra{4, nullptr, nullptr};

    TreeNode l{2, &a, nullptr};
    TreeNode r{2, nullptr, &b};

    r.left = &extra;

    TreeNode root{1, &l, &r};

    check(
        !isSymmetric(&root),
        "different subtree shape");
  }

  // Both sides have children, but the children are not mirrored.
  //
  //       1
  //      / \
  //     2   2
  //    /     \
  //   3       4
  {
    TreeNode a{3, nullptr, nullptr};
    TreeNode b{4, nullptr, nullptr};

    TreeNode l{2, &a, nullptr};
    TreeNode r{2, nullptr, &b};

    TreeNode root{1, &l, &r};

    check(
        !isSymmetric(&root),
        "same shape mismatch in mirrored values");
  }

  // Symmetric tree with one-sided descendants.
  //
  //         1
  //        / \
  //       2   2
  //        \ /
  //         3
  {
    TreeNode a{3, nullptr, nullptr};
    TreeNode b{3, nullptr, nullptr};

    TreeNode l{2, nullptr, &a};
    TreeNode r{2, &b, nullptr};

    TreeNode root{1, &l, &r};

    check(
        isSymmetric(&root),
        "deep mirrored one-sided children");
  }

  // Clearly asymmetric shape.
  {
    TreeNode a{2, nullptr, nullptr};
    TreeNode b{3, nullptr, nullptr};

    TreeNode l{2, nullptr, nullptr};
    TreeNode r{2, &b, nullptr};

    TreeNode root{1, &l, &r};

    check(
        !isSymmetric(&root),
        "one side has extra descendant");
  }

  // Deeper symmetric tree.
  //
  //           1
  //        /     \
  //       2       2
  //      / \     / \
  //     3   4   4   3
  //        /     \
  //       5       5
  {
    TreeNode a{3, nullptr, nullptr};
    TreeNode b{5, nullptr, nullptr};
    TreeNode c{4, nullptr, &b};

    TreeNode d{4, &b, nullptr};
    TreeNode e{3, nullptr, nullptr};

    TreeNode l{2, &a, &c};
    TreeNode r{2, &d, &e};

    TreeNode root{1, &l, &r};

    check(
        isSymmetric(&root),
        "deep symmetric tree");
  }

  // Root values don't match between children.
  {
    TreeNode l{2, nullptr, nullptr};
    TreeNode r{3, nullptr, nullptr};

    TreeNode root{1, &l, &r};

    check(
        !isSymmetric(&root),
        "root child values differ");
  }

  // Perfectly symmetric tree with duplicate values.
  {
    TreeNode a{5, nullptr, nullptr};
    TreeNode b{5, nullptr, nullptr};
    TreeNode c{5, nullptr, nullptr};
    TreeNode d{5, nullptr, nullptr};

    TreeNode l{5, &a, &b};
    TreeNode r{5, &c, &d};

    TreeNode root{5, &l, &r};

    check(
        isSymmetric(&root),
        "duplicate values remain symmetric");
  }

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
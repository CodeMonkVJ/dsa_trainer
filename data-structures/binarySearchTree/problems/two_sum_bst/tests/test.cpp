#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

static TreeNode *node(int v,
                      TreeNode *l = nullptr,
                      TreeNode *r = nullptr) {
  auto *n = new TreeNode(v);
  n->left = l;
  n->right = r;
  return n;
}

static void destroy(TreeNode *r) {
  if (!r)
    return;

  destroy(r->left);
  destroy(r->right);
  delete r;
}

int main() {
  int passed = 0, total = 0;

  auto check = [&](bool ok, const char *name) {
    ++total;
    if (ok)
      ++passed;

    cout << "DSA_CASE {\"input\":{\"case\":\""
         << name
         << "\"},\"expected\":true,\"actual\":"
         << (ok ? "true" : "false")
         << ",\"passed\":"
         << (ok ? "true" : "false")
         << "}\n";

    cout << (ok ? "PASS " : "FAIL ")
         << name << '\n';
  };

  // Balanced BST:
  //
  //        5
  //      /   \
  //     3     7
  //    / \   / \
  //   2   4 6   8
  {
    TreeNode *root =
        node(5,
             node(3, node(2), node(4)),
             node(7, node(6), node(8)));

    check(
        findTarget(root, 9),
        "pair across subtrees");

    check(
        findTarget(root, 10),
        "pair uses two internal values");

    check(
        findTarget(root, 7),
        "pair uses smallest values");

    check(
        findTarget(root, 13),
        "pair uses root and large value");

    check(
        findTarget(root, 14),
        "pair uses two largest values");

    check(
        !findTarget(root, 20),
        "target too large");

    check(
        !findTarget(root, 4),
        "target too small");

    check(
        !findTarget(root, 16),
        "no valid distinct pair");

    destroy(root);
  }

  // Single node cannot be reused.
  {
    TreeNode *root = node(5);

    check(
        !findTarget(root, 10),
        "single node cannot be used twice");

    check(
        !findTarget(root, 5),
        "single node no pair");

    destroy(root);
  }

  // Two-node BST.
  {
    TreeNode *root =
        node(5,
             node(3),
             nullptr);

    check(
        findTarget(root, 8),
        "two node valid pair");

    check(
        !findTarget(root, 6),
        "two node invalid pair");

    destroy(root);
  }

  // Left-skewed BST.
  {
    TreeNode *root =
        node(5,
             node(4,
                  node(3,
                       node(2,
                            node(1)))));

    check(
        findTarget(root, 6),
        "left skew pair");

    check(
        findTarget(root, 9),
        "left skew endpoint pair");

    check(
        !findTarget(root, 10),
        "left skew cannot reuse five");

    destroy(root);
  }

  // Right-skewed BST.
  {
    TreeNode *root =
        node(1,
             nullptr,
             node(2,
                  nullptr,
                  node(3,
                       nullptr,
                       node(4,
                            nullptr,
                            node(5)))));

    check(
        findTarget(root, 6),
        "right skew pair");

    check(
        findTarget(root, 9),
        "right skew largest pair");

    check(
        !findTarget(root, 2),
        "right skew cannot reuse one");

    destroy(root);
  }

  // Negative and positive values.
  {
    TreeNode *root =
        node(0,
             node(-10,
                  node(-20),
                  node(-5)),
             node(10,
                  node(5),
                  node(20)));

    check(
        findTarget(root, 0),
        "negative plus positive");

    check(
        findTarget(root, -15),
        "two negative values");

    check(
        findTarget(root, 15),
        "two positive values");

    check(
        !findTarget(root, 40),
        "no large positive pair");

    destroy(root);
  }

  // Requires several iterator advances.
  {
    TreeNode *root =
        node(8,
             node(4,
                  node(2,
                       node(1),
                       node(3)),
                  node(6,
                       node(5),
                       node(7))),
             node(12,
                  node(10,
                       node(9),
                       node(11)),
                  node(14,
                       node(13),
                       node(15))));

    check(
        findTarget(root, 16),
        "many iterator advances");

    check(
        findTarget(root, 27),
        "pair near upper end");

    check(
        !findTarget(root, 31),
        "iterators cross without match");

    destroy(root);
  }

  // Integer extremes.
  {
    TreeNode *root =
        node(0,
             node(INT_MIN),
             node(INT_MAX));

    check(
        findTarget(root, -1),
        "integer extremes sum");

    check(
        findTarget(root, INT_MAX),
        "extreme values no valid pair");

    destroy(root);
  }

  // Duplicate values, if duplicates are permitted in the BST.
  // Two distinct nodes with value 5 may form target 10.
  {
    TreeNode *root =
        node(5,
             node(3),
             node(5));

    check(
        findTarget(root, 10),
        "duplicate values on distinct nodes");

    destroy(root);
  }

  check(
      !findTarget(nullptr, 0),
      "empty tree");

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
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

  string input = "{\"case\":\"" + string(name) + "\"}";

  dsa_test::emit_case(
      input,
      "true",
      ok ? "true" : "false",
      ok);
}

TreeNode *n(int v,
            TreeNode *left = nullptr,
            TreeNode *right = nullptr) {
  TreeNode *node = new TreeNode(v);
  node->left = left;
  node->right = right;
  return node;
}

void destroy(TreeNode *root) {
  if (!root)
    return;

  destroy(root->left);
  destroy(root->right);
  delete root;
}

int main() {
  // Empty tree.
  check(
      boundaryTraversal(nullptr).empty(),
      "empty tree");

  // Single node.
  {
    TreeNode *root = n(9);

    check(
        boundaryTraversal(root) == vector<int>({9}),
        "single node");

    destroy(root);
  }

  // Complete binary tree.
  {
    TreeNode *root =
        n(1,
          n(2, n(4), n(5)),
          n(3, n(6), n(7)));

    check(
        boundaryTraversal(root) ==
            vector<int>({1, 2, 4, 5, 6, 7, 3}),
        "complete tree");

    destroy(root);
  }

  // Only left subtree.
  {
    TreeNode *root =
        n(1,
          n(2,
            n(3,
              n(4))),
          nullptr);

    check(
        boundaryTraversal(root) ==
            vector<int>({1, 2, 3, 4}),
        "left skewed tree");

    destroy(root);
  }

  // Only right subtree.
  {
    TreeNode *root =
        n(1,
          nullptr,
          n(2,
            nullptr,
            n(3,
              nullptr,
              n(4))));

    check(
        boundaryTraversal(root) ==
            vector<int>({1, 4, 3, 2}),
        "right skewed tree");

    destroy(root);
  }

  // Left boundary must fall back to right child.
  //
  //       1
  //      /
  //     2
  //      \
  //       3
  //        \
  //         4
  {
    TreeNode *root =
        n(1,
          n(2,
            nullptr,
            n(3,
              nullptr,
              n(4))),
          nullptr);

    check(
        boundaryTraversal(root) ==
            vector<int>({1, 2, 3, 4}),
        "left boundary follows right fallback");

    destroy(root);
  }

  // Right boundary must fall back to left child.
  //
  //     1
  //      \
  //       2
  //      /
  //     3
  //    /
  //   4
  {
    TreeNode *root =
        n(1,
          nullptr,
          n(2,
            n(3,
              n(4),
              nullptr),
            nullptr));

    check(
        boundaryTraversal(root) ==
            vector<int>({1, 4, 3, 2}),
        "right boundary follows left fallback");

    destroy(root);
  }

  // Leaves on the boundary must not be duplicated.
  {
    TreeNode *root =
        n(1,
          n(2),
          n(3));

    check(
        boundaryTraversal(root) ==
            vector<int>({1, 2, 3}),
        "boundary leaves not duplicated");

    destroy(root);
  }

  // One child only.
  {
    TreeNode *root =
        n(1,
          n(2),
          nullptr);

    check(
        boundaryTraversal(root) ==
            vector<int>({1, 2}),
        "single left child");

    destroy(root);
  }

  {
    TreeNode *root =
        n(1,
          nullptr,
          n(2));

    check(
        boundaryTraversal(root) ==
            vector<int>({1, 2}),
        "single right child");

    destroy(root);
  }

  // Irregular tree.
  //
  //          1
  //        /   \
  //       2     3
  //        \   /
  //         4 5
  //        /   \
  //       6     7
  {
    TreeNode *root =
        n(1,
          n(2,
            nullptr,
            n(4,
              n(6),
              nullptr)),
          n(3,
            n(5,
              nullptr,
              n(7)),
            nullptr));

    check(
        boundaryTraversal(root) ==
            vector<int>({1, 2, 4, 6, 7, 5, 3}),
        "irregular tree");

    destroy(root);
  }

  // Multiple leaves inside the tree.
  {
    TreeNode *root =
        n(10,
          n(5,
            n(2),
            n(7,
              n(6),
              n(8))),
          n(20,
            n(15),
            n(25)));

    check(
        boundaryTraversal(root) ==
            vector<int>({10, 5, 2, 6, 8, 15, 25, 20}),
        "multiple interior leaves");

    destroy(root);
  }

  // Deep mixed tree.
  {
    TreeNode *root =
        n(1,
          n(2,
            n(4,
              nullptr,
              n(8)),
            n(5)),
          n(3,
            n(6,
              n(9),
              nullptr),
            n(7,
              nullptr,
              n(10))));

    check(
        boundaryTraversal(root) ==
            vector<int>({1, 2, 4, 8, 5, 9, 10, 7, 3}),
        "deep mixed tree");

    destroy(root);
  }

  // Root with only two deep leaves.
  {
    TreeNode *root =
        n(1,
          n(2,
            nullptr,
            n(4)),
          n(3,
            n(5),
            nullptr));

    check(
        boundaryTraversal(root) ==
            vector<int>({1, 2, 4, 5, 3}),
        "deep leaves on both sides");

    destroy(root);
  }

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
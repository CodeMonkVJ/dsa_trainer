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

  string input = "{\"case\":\"" + string(name) + "\"}";
  dsa_test::emit_case(input, "true", ok ? "true" : "false", ok);
}

static TreeNode *n(int v,
                   TreeNode *left = nullptr,
                   TreeNode *right = nullptr) {
  TreeNode *x = new TreeNode(v);
  x->left = left;
  x->right = right;
  return x;
}

static void destroy(TreeNode *root) {
  if (!root)
    return;

  destroy(root->left);
  destroy(root->right);
  delete root;
}

int main() {
  check(
      verticalOrder(nullptr).empty(),
      "empty tree");

  {
    TreeNode *root = n(42);

    check(
        verticalOrder(root) == vector<vector<int>>{{42}},
        "single node");

    destroy(root);
  }

  //        3
  //       / \
  //      9   20
  //         /  \
  //        15   7
  {
    TreeNode *root =
        n(3,
          n(9),
          n(20,
            n(15),
            n(7)));

    check(
        verticalOrder(root) ==
            vector<vector<int>>{
                {9},
                {3, 15},
                {20},
                {7}},
        "standard columns");

    destroy(root);
  }

  //        1
  //       / \
  //      2   3
  //       \ /
  //       4 5
  //
  // 4 and 5 are same row and same column.
  // BFS should preserve 4 before 5.
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
        verticalOrder(root) ==
            vector<vector<int>>{
                {2},
                {1, 4, 5},
                {3}},
        "same row same column left to right");

    destroy(root);
  }

  // Left skewed:
  //
  //       4
  //      /
  //     3
  //    /
  //   2
  //  /
  // 1
  {
    TreeNode *root =
        n(4,
          n(3,
            n(2,
              n(1))),
          nullptr);

    check(
        verticalOrder(root) ==
            vector<vector<int>>{
                {1},
                {2},
                {3},
                {4}},
        "left skewed tree");

    destroy(root);
  }

  // Right skewed:
  //
  // 1
  //  \
  //   2
  //    \
  //     3
  //      \
  //       4
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
        verticalOrder(root) ==
            vector<vector<int>>{
                {1},
                {2},
                {3},
                {4}},
        "right skewed tree");

    destroy(root);
  }

  // Full balanced tree:
  //
  //          1
  //        /   \
  //       2     3
  //      / \   / \
  //     4   5 6   7
  //
  // Columns:
  // -2: 4
  // -1: 2
  //  0: 1,5,6
  //  1: 3
  //  2: 7
  {
    TreeNode *root =
        n(1,
          n(2,
            n(4),
            n(5)),
          n(3,
            n(6),
            n(7)));

    check(
        verticalOrder(root) ==
            vector<vector<int>>{
                {4},
                {2},
                {1, 5, 6},
                {3},
                {7}},
        "balanced tree with center collisions");

    destroy(root);
  }

  // Same column across different depths.
  //
  //          1
  //         /
  //        2
  //         \
  //          3
  //           \
  //            4
  //
  // columns:
  // 1 -> 0
  // 2 -> -1
  // 3 -> 0
  // 4 -> 1
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
        verticalOrder(root) ==
            vector<vector<int>>{
                {2},
                {1, 3},
                {4}},
        "same column different depths");

    destroy(root);
  }

  // Wider irregular tree.
  //
  //             10
  //           /    \
  //          5      15
  //         / \    /  \
  //        3   7  12  18
  //         \ /      \
  //          4 6      13
  //
  {
    TreeNode *root =
        n(10,
          n(5,
            n(3,
              nullptr,
              n(4)),
            n(7,
              n(6),
              nullptr)),
          n(15,
            n(12,
              nullptr,
              n(13)),
            n(18)));

    check(
        verticalOrder(root) ==
            vector<vector<int>>{
                {3},
                {5, 4, 6},
                {10, 7, 12},
                {15, 13},
                {18}},
        "irregular multi column tree");

    destroy(root);
  }

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
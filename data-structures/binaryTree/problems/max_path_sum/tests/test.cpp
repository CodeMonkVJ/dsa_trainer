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

  dsa_test::emit_case(
      input,
      "true",
      ok ? "true" : "false",
      ok);

  cout << (ok ? "PASS " : "FAIL ")
       << name << '\n';
}

TreeNode *n(int v,
            TreeNode *l = nullptr,
            TreeNode *r = nullptr) {
  auto *x = new TreeNode(v);
  x->left = l;
  x->right = r;
  return x;
}

void destroy(TreeNode *root) {
  if (!root)
    return;

  destroy(root->left);
  destroy(root->right);
  delete root;
}

int main() {
  // Empty tree, if this is your chosen contract.
  check(
      maxPathSum(nullptr) == numeric_limits<int>::min(),
      "empty tree");

  // Single positive node.
  {
    TreeNode *root = n(5);

    check(
        maxPathSum(root) == 5,
        "single positive node");

    destroy(root);
  }

  // Single negative node.
  {
    TreeNode *root = n(-7);

    check(
        maxPathSum(root) == -7,
        "single negative node");

    destroy(root);
  }

  // Classic case: best path lies entirely in right subtree.
  {
    TreeNode *root =
        n(-10,
          n(9),
          n(20,
            n(15),
            n(7)));

    check(
        maxPathSum(root) == 42,
        "best path skips root");

    destroy(root);
  }

  // All negative values: choose the least negative node.
  {
    TreeNode *root =
        n(-3,
          n(-2),
          n(-1));

    check(
        maxPathSum(root) == -1,
        "all negative");

    destroy(root);
  }

  // Best path goes through root.
  {
    TreeNode *root =
        n(10,
          n(2),
          n(10));

    check(
        maxPathSum(root) == 22,
        "best path through root");

    destroy(root);
  }

  // Both child branches contribute.
  {
    TreeNode *root =
        n(1,
          n(2),
          n(3));

    check(
        maxPathSum(root) == 6,
        "uses both child branches");

    destroy(root);
  }

  // Negative child should be ignored.
  {
    TreeNode *root =
        n(5,
          n(-10),
          n(4));

    check(
        maxPathSum(root) == 9,
        "ignores negative contribution");

    destroy(root);
  }

  // Best path is a single node inside a mixed tree.
  {
    TreeNode *root =
        n(-10,
          n(-20),
          n(5,
            n(-30),
            n(-40)));

    check(
        maxPathSum(root) == 5,
        "best path is single internal node");

    destroy(root);
  }

  // Left-skewed positive tree.
  {
    TreeNode *root =
        n(5,
          n(4,
            n(3,
              n(2,
                n(1)))));

    check(
        maxPathSum(root) == 15,
        "left skewed positive");

    destroy(root);
  }

  // Right-skewed mixed values.
  {
    TreeNode *root =
        n(5,
          nullptr,
          n(-2,
            nullptr,
            n(10,
              nullptr,
              n(3))));

    check(
        maxPathSum(root) == 16,
        "right skewed mixed values");

    destroy(root);
  }

  // Path starts and ends at leaves below an internal node.
  {
    TreeNode *root =
        n(5,
          n(4),
          n(8,
            n(11,
              n(7),
              n(2)),
            n(1)));

    check(
        maxPathSum(root) == 35,
        "best path through internal subtree");

    destroy(root);
  }

  // Negative root, profitable subtrees on both sides.
  {
    TreeNode *root =
        n(-1,
          n(10),
          n(20));

    check(
        maxPathSum(root) == 29,
        "negative root still connects profitable sides");

    destroy(root);
  }

  // Zero values.
  {
    TreeNode *root =
        n(0,
          n(0),
          n(0));

    check(
        maxPathSum(root) == 0,
        "all zero values");

    destroy(root);
  }

  // Duplicate values.
  {
    TreeNode *root =
        n(5,
          n(5),
          n(5));

    check(
        maxPathSum(root) == 15,
        "duplicate values");

    destroy(root);
  }

  // Deeper tree where best path avoids root.
  {
    TreeNode *root =
        n(-100,
          n(1),
          n(10,
            n(20,
              n(30),
              n(40)),
            n(5)));

    check(
        maxPathSum(root) == 90,
        "deep best path avoids root");

    destroy(root);
  }

  // INT extremes without overflowing the expected sum.
  {
    TreeNode *root =
        n(INT_MIN,
          n(1),
          n(2));

    check(
        maxPathSum(root) == 2,
        "integer minimum node");

    destroy(root);
  }

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
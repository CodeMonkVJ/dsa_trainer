#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

static TreeNode *n(int v,
                   TreeNode *l = nullptr,
                   TreeNode *r = nullptr) {
  auto *x = new TreeNode(v);
  x->left = l;
  x->right = r;
  return x;
}

static void del(TreeNode *r) {
  if (!r)
    return;

  del(r->left);
  del(r->right);
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

  check(
      isValidBST(nullptr),
      "empty tree is valid");

  {
    TreeNode *root = n(42);

    check(
        isValidBST(root),
        "single node");

    del(root);
  }

  {
    TreeNode *root =
        n(2,
          n(1),
          n(3));

    check(
        isValidBST(root),
        "simple valid bst");

    del(root);
  }

  // Classic ancestor violation:
  //
  //       5
  //      / \
  //     1   4
  //        / \
  //       3   6
  //
  // Node 4 is in the right subtree of 5 but 4 < 5.
  {
    TreeNode *root =
        n(5,
          n(1),
          n(4,
            n(3),
            n(6)));

    check(
        !isValidBST(root),
        "ancestor violation on right subtree");

    del(root);
  }

  // Immediate parent-child relationships look fine,
  // but 6 violates ancestor 10.
  //
  //       10
  //      /  \
  //     5    15
  //         /  \
  //        6    20
  {
    TreeNode *root =
        n(10,
          n(5),
          n(15,
            n(6),
            n(20)));

    check(
        !isValidBST(root),
        "deep right subtree violates ancestor");

    del(root);
  }

  // Mirror ancestor violation.
  //
  //       10
  //      /  \
  //     5    15
  //    / \
  //   2  12
  {
    TreeNode *root =
        n(10,
          n(5,
            n(2),
            n(12)),
          n(15));

    check(
        !isValidBST(root),
        "deep left subtree violates ancestor");

    del(root);
  }

  // Duplicate directly on left.
  {
    TreeNode *root =
        n(5,
          n(5),
          n(7));

    check(
        !isValidBST(root),
        "duplicate on left invalid");

    del(root);
  }

  // Duplicate directly on right.
  {
    TreeNode *root =
        n(5,
          n(3),
          n(5));

    check(
        !isValidBST(root),
        "duplicate on right invalid");

    del(root);
  }

  // Duplicate deeper in subtree.
  {
    TreeNode *root =
        n(10,
          n(5,
            n(2),
            n(10)),
          n(15));

    check(
        !isValidBST(root),
        "deep duplicate invalid");

    del(root);
  }

  // Valid left-skewed BST.
  {
    TreeNode *root =
        n(5,
          n(4,
            n(3,
              n(2,
                n(1)))));

    check(
        isValidBST(root),
        "left skewed valid bst");

    del(root);
  }

  // Valid right-skewed BST.
  {
    TreeNode *root =
        n(1,
          nullptr,
          n(2,
            nullptr,
            n(3,
              nullptr,
              n(4,
                nullptr,
                n(5)))));

    check(
        isValidBST(root),
        "right skewed valid bst");

    del(root);
  }

  // Negative values.
  {
    TreeNode *root =
        n(0,
          n(-10,
            n(-20),
            n(-5)),
          n(10,
            n(5),
            n(20)));

    check(
        isValidBST(root),
        "negative and positive values");

    del(root);
  }

  // Full int range.
  {
    TreeNode *root =
        n(0,
          n(INT_MIN),
          n(INT_MAX));

    check(
        isValidBST(root),
        "integer extremes valid");

    del(root);
  }

  // INT_MAX as root must be allowed.
  {
    TreeNode *root =
        n(INT_MAX,
          n(INT_MIN),
          nullptr);

    check(
        isValidBST(root),
        "INT_MAX root valid");

    del(root);
  }

  // INT_MIN as root must be allowed.
  {
    TreeNode *root =
        n(INT_MIN,
          nullptr,
          n(INT_MAX));

    check(
        isValidBST(root),
        "INT_MIN root valid");

    del(root);
  }

  // Duplicate INT_MIN.
  {
    TreeNode *root =
        n(INT_MIN,
          nullptr,
          n(INT_MIN));

    check(
        !isValidBST(root),
        "duplicate INT_MIN invalid");

    del(root);
  }

  // Duplicate INT_MAX.
  {
    TreeNode *root =
        n(INT_MAX,
          n(INT_MAX),
          nullptr);

    check(
        !isValidBST(root),
        "duplicate INT_MAX invalid");

    del(root);
  }

  // Larger valid BST.
  {
    TreeNode *root =
        n(8,
          n(3,
            n(1),
            n(6,
              n(4),
              n(7))),
          n(10,
            nullptr,
            n(14,
              n(13),
              nullptr)));

    check(
        isValidBST(root),
        "larger valid bst");

    del(root);
  }

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
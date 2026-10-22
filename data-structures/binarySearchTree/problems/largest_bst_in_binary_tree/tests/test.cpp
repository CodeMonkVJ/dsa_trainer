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

  cout << "DSA_CASE {\"input\":{\"case\":\""
       << name
       << "\"},\"expected\":true,\"actual\":"
       << (ok ? "true" : "false")
       << ",\"passed\":"
       << (ok ? "true" : "false")
       << "}\n";
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
  // Empty tree.
  check(
      largestBST(nullptr) == 0,
      "empty tree");

  // Single node.
  {
    TreeNode *root = n(42);

    check(
        largestBST(root) == 1,
        "single node");

    destroy(root);
  }

  // Entire tree is a BST.
  {
    TreeNode *root =
        n(5,
          n(2, n(1), n(3)),
          n(8, n(6), n(10)));

    check(
        largestBST(root) == 7,
        "entire tree is BST");

    destroy(root);
  }

  // Invalid root, both child subtrees are valid BSTs.
  {
    TreeNode *root =
        n(10,
          n(5, n(1), n(8)),
          n(15, n(7), n(20)));

    check(
        largestBST(root) == 3,
        "largest BST below invalid root");

    destroy(root);
  }

  // Root violates both sides.
  {
    TreeNode *root =
        n(5,
          n(6),
          n(4));

    check(
        largestBST(root) == 1,
        "both children violate root");

    destroy(root);
  }

  // Strict ordering: duplicate on left is invalid.
  {
    TreeNode *root =
        n(5,
          n(5),
          n(8));

    check(
        largestBST(root) == 1,
        "duplicate on left invalid");

    destroy(root);
  }

  // Strict ordering: duplicate on right is invalid.
  {
    TreeNode *root =
        n(5,
          n(2),
          n(5));

    check(
        largestBST(root) == 1,
        "duplicate on right invalid");

    destroy(root);
  }

  // Duplicate deeper in subtree invalidates the larger subtree.
  {
    TreeNode *root =
        n(10,
          n(5,
            n(2),
            n(10)),
          n(15));

    check(
        largestBST(root) == 3,
        "deep duplicate breaks BST");

    destroy(root);
  }

  // Left-skewed valid BST.
  {
    TreeNode *root =
        n(5,
          n(4,
            n(3,
              n(2,
                n(1)))),
          nullptr);

    check(
        largestBST(root) == 5,
        "left skewed BST");

    destroy(root);
  }

  // Right-skewed valid BST.
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
        largestBST(root) == 5,
        "right skewed BST");

    destroy(root);
  }

  // Invalidity is deep and not directly between root and child.
  {
    TreeNode *root =
        n(20,
          n(10,
            n(5),
            n(25)),   // 25 makes this left subtree invalid for 20
          n(30,
            n(22),
            n(40)));

    check(
        largestBST(root) == 3,
        "deep ordering violation");

    destroy(root);
  }

  // Largest BST is in the left subtree.
  {
    TreeNode *root =
        n(50,
          n(20,
            n(10),
            n(30,
              n(25),
              n(35))),
          n(40)); // invalid relative to root

    check(
        largestBST(root) == 5,
        "largest BST on left");

    destroy(root);
  }

  // Largest BST is in the right subtree.
  {
    TreeNode *root =
        n(10,
          n(20), // invalid relative to root
          n(30,
            n(25),
            n(40,
              n(35),
              n(50))));

    check(
        largestBST(root) == 5,
        "largest BST on right");

    destroy(root);
  }

  // Equal-sized BSTs on both sides.
  {
    TreeNode *root =
        n(10,
          n(5, n(1), n(8)),
          n(15, n(7), n(20)));

    check(
        largestBST(root) == 3,
        "equal largest BSTs on both sides");

    destroy(root);
  }

  // Negative values.
  {
    TreeNode *root =
        n(-5,
          n(-10, n(-20), n(-7)),
          n(0, n(-2), n(5)));

    check(
        largestBST(root) == 7,
        "negative values");

    destroy(root);
  }

  // Mixed valid and invalid negative values.
  {
    TreeNode *root =
        n(0,
          n(-5, n(-10), n(2)),
          n(10));

    check(
        largestBST(root) == 3,
        "negative subtree with violation");

    destroy(root);
  }

  // Integer extremes.
  {
    TreeNode *root =
        n(0,
          n(INT_MIN),
          n(INT_MAX));

    check(
        largestBST(root) == 3,
        "integer extremes");

    destroy(root);
  }

  // Only leaves are valid BSTs.
  {
    TreeNode *root =
        n(10,
          n(20,
            n(30),
            n(25)),
          n(5,
            n(8),
            n(1)));

    check(
        largestBST(root) == 1,
        "largest BST is a leaf");

    destroy(root);
  }

  // Irregular but entirely valid BST.
  {
    TreeNode *root =
        n(20,
          n(8,
            n(4),
            n(12,
              n(10),
              n(14))),
          n(30,
            n(25),
            n(40,
              nullptr,
              n(50))));

    check(
        largestBST(root) == 10,
        "irregular entire BST");

    destroy(root);
  }

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
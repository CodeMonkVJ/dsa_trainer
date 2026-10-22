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

  /*
              6
            /   \
           2     8
          / \   / \
         0   4 7   9
            / \
           3   5
  */
  TreeNode *root =
      n(6,
        n(2,
          n(0),
          n(4,
            n(3),
            n(5))),
        n(8,
          n(7),
          n(9)));

  // LCA is root.
  check(
      lcaBST(root, 2, 8) == root,
      "lca is root");

  // Split inside left subtree.
  {
    TreeNode *ans = lcaBST(root, 3, 5);

    check(
        ans != nullptr && ans->val == 4,
        "siblings under internal node");
  }

  // LCA is ancestor of one key.
  {
    TreeNode *ans = lcaBST(root, 2, 5);

    check(
        ans != nullptr && ans->val == 2,
        "one key is ancestor of other");
  }

  // Same idea on right side.
  {
    TreeNode *ans = lcaBST(root, 8, 9);

    check(
        ans != nullptr && ans->val == 8,
        "ancestor case on right");
  }

  // Keys far apart.
  {
    TreeNode *ans = lcaBST(root, 0, 9);

    check(
        ans != nullptr && ans->val == 6,
        "keys on opposite extremes");
  }

  // LCA deeper in left subtree.
  {
    TreeNode *ans = lcaBST(root, 3, 4);

    check(
        ans != nullptr && ans->val == 4,
        "one key is direct ancestor");
  }

  // Both keys in right subtree.
  {
    TreeNode *ans = lcaBST(root, 7, 9);

    check(
        ans != nullptr && ans->val == 8,
        "both keys in right subtree");
  }

  // First key missing.
  check(
      lcaBST(root, 42, 5) == nullptr,
      "first key missing");

  // Second key missing.
  check(
      lcaBST(root, 3, 42) == nullptr,
      "second key missing");

  // Both keys missing.
  check(
      lcaBST(root, 41, 42) == nullptr,
      "both keys missing");

  // Missing key whose hypothetical search path would split
  // at a valid node.
  check(
      lcaBST(root, 3, 1) == nullptr,
      "missing key despite apparent split");

  // Empty tree.
  check(
      lcaBST(nullptr, 1, 2) == nullptr,
      "empty tree");

  // Smallest non-trivial BST.
  {
    TreeNode *r = n(2, n(1), n(3));

    TreeNode *ans = lcaBST(r, 1, 3);

    check(
        ans != nullptr && ans->val == 2,
        "three node bst");

    del(r);
  }

  // Left-skewed BST.
  {
    TreeNode *r =
        n(5,
          n(4,
            n(3,
              n(2,
                n(1)))));

    TreeNode *ans = lcaBST(r, 1, 3);

    check(
        ans != nullptr && ans->val == 3,
        "left skewed tree");

    del(r);
  }

  // Right-skewed BST.
  {
    TreeNode *r =
        n(1,
          nullptr,
          n(2,
            nullptr,
            n(3,
              nullptr,
              n(4,
                nullptr,
                n(5)))));

    TreeNode *ans = lcaBST(r, 3, 5);

    check(
        ans != nullptr && ans->val == 3,
        "right skewed tree");

    del(r);
  }

  // Negative values.
  {
    TreeNode *r =
        n(0,
          n(-10,
            n(-20),
            n(-5)),
          n(10,
            n(5),
            n(20)));

    TreeNode *ans = lcaBST(r, -20, -5);

    check(
        ans != nullptr && ans->val == -10,
        "negative keys");

    del(r);
  }

  // Extreme integer values.
  {
    TreeNode *r =
        n(0,
          n(INT_MIN),
          n(INT_MAX));

    TreeNode *ans = lcaBST(r, INT_MIN, INT_MAX);

    check(
        ans != nullptr && ans->val == 0,
        "integer extremes");

    del(r);
  }

  del(root);

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
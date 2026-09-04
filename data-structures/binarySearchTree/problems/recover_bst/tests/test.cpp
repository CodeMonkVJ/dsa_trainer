#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

void check(bool ok, const char *s) {
  ++total;
  if (ok)
    ++passed;

  cout << "DSA_CASE {\"input\":{\"case\":\"" << s
       << "\"},\"expected\":true,\"actual\":"
       << (ok ? "true" : "false")
       << ",\"passed\":" << (ok ? "true" : "false")
       << "}\n";
}

TreeNode *n(int v, TreeNode *l = nullptr, TreeNode *r = nullptr) {
  auto *x = new TreeNode(v);
  x->left = l;
  x->right = r;
  return x;
}

void inorder(TreeNode *root, vector<int> &out) {
  if (!root)
    return;

  inorder(root->left, out);
  out.push_back(root->val);
  inorder(root->right, out);
}

vector<int> in(TreeNode *root) {
  vector<int> result;
  inorder(root, result);
  return result;
}

void destroy(TreeNode *root) {
  if (!root)
    return;

  destroy(root->left);
  destroy(root->right);
  delete root;
}

int main() {
  // Non-adjacent swap.
  //
  //       3
  //      / \
  //     1   4
  //        /
  //       2
  {
    auto *t = n(3, n(1), n(4, n(2), nullptr));

    recoverBST(t);

    check(in(t) == vector<int>({1, 2, 3, 4}),
          "recovers non-adjacent swap");

    destroy(t);
  }

  // Adjacent values in inorder are swapped.
  {
    auto *t = n(2, n(3), n(1));

    recoverBST(t);

    check(in(t) == vector<int>({1, 2, 3}),
          "recovers adjacent swap");

    destroy(t);
  }

  // Root and leaf swapped.
  //
  // Correct tree would have values:
  //       4
  //      / \
  //     2   6
  //    / \
  //   1   3
  //
  // Swap values 4 and 1.
  {
    auto *t = n(1,
                n(2, n(4), n(3)),
                n(6));

    recoverBST(t);

    check(in(t) == vector<int>({1, 2, 3, 4, 6}),
          "recovers root and leaf swap");

    destroy(t);
  }

  // Swap minimum and maximum.
  {
    auto *t = n(3,
                n(5, n(1), nullptr),
                n(4, nullptr, n(2)));

    recoverBST(t);

    check(in(t) == vector<int>({1, 2, 3, 4, 5}),
          "recovers minimum and maximum swap");

    destroy(t);
  }

  // Left-skewed tree.
  {
    auto *t = n(4,
                n(2,
                  n(3,
                    n(1),
                    nullptr),
                  nullptr),
                nullptr);

    recoverBST(t);

    check(in(t) == vector<int>({1, 2, 3, 4}),
          "recovers skewed tree");

    destroy(t);
  }

  // Single node should remain unchanged.
  {
    auto *t = n(42);

    recoverBST(t);

    check(t->val == 42 &&
              t->left == nullptr &&
              t->right == nullptr,
          "handles single node");

    destroy(t);
  }

  // Already valid tree should remain unchanged.
  {
    auto *t = n(4,
                n(2, n(1), n(3)),
                n(6, n(5), n(7)));

    const auto before = in(t);

    recoverBST(t);

    check(in(t) == before,
          "leaves valid tree unchanged");

    destroy(t);
  }

  // Negative values.
  {
    // Correct inorder should be:
    // -10, -5, -2, 0, 4
    //
    // -5 and 4 have been swapped.
    auto *t = n(0,
                n(4, n(-10), n(-2)),
                n(-5));

    recoverBST(t);

    check(in(t) == vector<int>({-10, -5, -2, 0, 4}),
          "handles negative values");

    destroy(t);
  }

  // Extreme integer values.
  {
    auto *t = n(0,
                n(INT_MAX),
                n(INT_MIN));

    recoverBST(t);

    check(in(t) == vector<int>({INT_MIN, 0, INT_MAX}),
          "handles extreme integer values");

    destroy(t);
  }

  // Verify that recovery changes values, not tree structure.
  {
    auto *left = n(3);
    auto *right = n(1);
    auto *root = n(2, left, right);

    recoverBST(root);

    check(root->left == left &&
              root->right == right &&
              in(root) == vector<int>({1, 2, 3}),
          "preserves tree structure");

    destroy(root);
  }

  // Empty tree.
  {
    recoverBST(nullptr);
    check(true, "handles empty tree");
  }

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
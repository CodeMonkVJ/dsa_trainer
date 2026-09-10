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

  cout << "DSA_CASE {\"input\":{\"case\":\"" << name
       << "\"},\"expected\":true,\"actual\":"
       << (ok ? "true" : "false")
       << ",\"passed\":" << (ok ? "true" : "false")
       << "}\n";

  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

TreeNode *n(int v, TreeNode *l = nullptr, TreeNode *r = nullptr) {
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
  // Two disjoint BSTs.
  {
    TreeNode *a = n(1, n(0), n(5));
    TreeNode *b = n(2, n(1), n(6));

    check(
        mergeBSTs(a, b) == vector<int>({0, 1, 1, 2, 5, 6}),
        "merges two disjoint trees");

    destroy(a);
    destroy(b);
  }

  // Shared keys must appear twice.
  {
    TreeNode *a = n(3, n(1), n(5));
    TreeNode *b = n(3, n(2), n(5));

    check(
        mergeBSTs(a, b) == vector<int>({1, 2, 3, 3, 5, 5}),
        "preserves duplicate keys");

    destroy(a);
    destroy(b);
  }

  // One tree is empty.
  {
    TreeNode *a = n(2, n(1), n(4));

    check(
        mergeBSTs(a, nullptr) == vector<int>({1, 2, 4}),
        "first tree only");

    check(
        mergeBSTs(nullptr, a) == vector<int>({1, 2, 4}),
        "second tree only");

    destroy(a);
  }

  // Both trees empty.
  {
    check(
        mergeBSTs(nullptr, nullptr).empty(),
        "both trees empty");
  }

  // Single-node trees.
  {
    TreeNode *a = n(5);
    TreeNode *b = n(2);

    check(
        mergeBSTs(a, b) == vector<int>({2, 5}),
        "single-node trees");

    destroy(a);
    destroy(b);
  }

  // One tree contains duplicate keys internally.
  {
    TreeNode *a = n(2, n(1), n(3));
    TreeNode *b = n(2, n(0), n(4));

    check(
        mergeBSTs(a, b) == vector<int>({0, 1, 2, 2, 3, 4}),
        "overlapping key ranges");

    destroy(a);
    destroy(b);
  }

  // Highly unbalanced trees.
  {
    TreeNode *a =
        n(1, nullptr,
          n(2, nullptr,
            n(3, nullptr,
              n(4))));

    TreeNode *b =
        n(10, n(8, n(7), nullptr), nullptr);

    check(
        mergeBSTs(a, b) ==
            vector<int>({1, 2, 3, 4, 7, 8, 10}),
        "unbalanced trees");

    destroy(a);
    destroy(b);
  }

  // Negative values.
  {
    TreeNode *a = n(-3, n(-8), n(-1));
    TreeNode *b = n(0, n(-5), n(4));

    check(
        mergeBSTs(a, b) ==
            vector<int>({-8, -5, -3, -1, 0, 4}),
        "negative values");

    destroy(a);
    destroy(b);
  }

  // Extreme integer values.
  {
    TreeNode *a = n(0, n(INT_MIN), n(INT_MAX));

    check(
        mergeBSTs(a, nullptr) ==
            vector<int>({INT_MIN, 0, INT_MAX}),
        "extreme integer values");

    destroy(a);
  }

  // Verify original trees remain unchanged.
  {
    TreeNode *a = n(3, n(1), n(5));
    TreeNode *b = n(4, n(2), n(6));

    auto beforeA = vector<int>({1, 3, 5});
    auto beforeB = vector<int>({2, 4, 6});

    auto merged = mergeBSTs(a, b);

    // Trees should still have their original structure/values.
    bool unchanged =
        a->val == 3 &&
        a->left->val == 1 &&
        a->right->val == 5 &&
        b->val == 4 &&
        b->left->val == 2 &&
        b->right->val == 6;

    check(
        merged == vector<int>({1, 2, 3, 4, 5, 6}) &&
            unchanged,
        "does not modify input trees");

    destroy(a);
    destroy(b);
  }

  // Interleaved values from both trees.
  {
    TreeNode *a =
        n(8, n(3, n(1), n(6)), n(10));

    TreeNode *b =
        n(7, n(2), n(9, nullptr, n(11)));

    check(
        mergeBSTs(a, b) ==
            vector<int>({1, 2, 3, 6, 7, 8, 9, 10, 11}),
        "interleaved values");

    destroy(a);
    destroy(b);
  }

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
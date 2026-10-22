#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

void check(bool x, const char *name) {
  ++total;
  if (x)
    ++passed;

  string input = "{\"case\":\"" + string(name) + "\"}";
  dsa_test::emit_case(input, "true", x ? "true" : "false", x);

  cout << (x ? "PASS " : "FAIL ")
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

vector<TreeNode *> preorderNodes(TreeNode *root) {
  vector<TreeNode *> out;

  if (!root)
    return out;

  stack<TreeNode *> st;
  st.push(root);

  while (!st.empty()) {
    TreeNode *cur = st.top();
    st.pop();

    out.push_back(cur);

    if (cur->right)
      st.push(cur->right);

    if (cur->left)
      st.push(cur->left);
  }

  return out;
}

bool validateFlattened(TreeNode *root,
                       const vector<TreeNode *> &expectedOrder) {
  vector<TreeNode *> actual;
  unordered_set<TreeNode *> seen;

  TreeNode *cur = root;

  while (cur) {
    if (seen.count(cur))
      return false; // cycle

    seen.insert(cur);

    if (cur->left != nullptr)
      return false;

    actual.push_back(cur);
    cur = cur->right;
  }

  return actual == expectedOrder;
}

void destroyFlattened(TreeNode *root) {
  while (root) {
    TreeNode *next = root->right;
    delete root;
    root = next;
  }
}

int main() {
  // Empty tree.
  {
    flatten(nullptr);
    check(true, "empty tree");
  }

  // Single node.
  {
    TreeNode *root = n(1);
    auto expected = preorderNodes(root);

    flatten(root);

    check(
        validateFlattened(root, expected),
        "single node");

    destroyFlattened(root);
  }

  // Classic example.
  {
    TreeNode *root =
        n(1,
          n(2,
            n(3),
            n(4)),
          n(5,
            nullptr,
            n(6)));

    auto expected = preorderNodes(root);

    flatten(root);

    check(
        validateFlattened(root, expected),
        "classic preorder flatten");

    destroyFlattened(root);
  }

  // Already right-skewed.
  {
    TreeNode *root =
        n(1,
          nullptr,
          n(2,
            nullptr,
            n(3,
              nullptr,
              n(4))));

    auto expected = preorderNodes(root);

    flatten(root);

    check(
        validateFlattened(root, expected),
        "already right skewed");

    destroyFlattened(root);
  }

  // Left-skewed tree.
  {
    TreeNode *root =
        n(1,
          n(2,
            n(3,
              n(4))),
          nullptr);

    auto expected = preorderNodes(root);

    flatten(root);

    check(
        validateFlattened(root, expected),
        "left skewed tree");

    destroyFlattened(root);
  }

  // Full balanced tree.
  {
    TreeNode *root =
        n(1,
          n(2,
            n(4),
            n(5)),
          n(3,
            n(6),
            n(7)));

    auto expected = preorderNodes(root);

    flatten(root);

    check(
        validateFlattened(root, expected),
        "balanced tree");

    destroyFlattened(root);
  }

  // Irregular tree.
  {
    TreeNode *root =
        n(1,
          n(2,
            nullptr,
            n(3,
              n(4),
              nullptr)),
          n(5,
            n(6,
              nullptr,
              n(7)),
            n(8)));

    auto expected = preorderNodes(root);

    flatten(root);

    check(
        validateFlattened(root, expected),
        "irregular tree");

    destroyFlattened(root);
  }

  // Left subtree has a long right spine.
  //
  //        1
  //       / \
  //      2   6
  //       \
  //        3
  //         \
  //          4
  //           \
  //            5
  //
  {
    TreeNode *root =
        n(1,
          n(2,
            nullptr,
            n(3,
              nullptr,
              n(4,
                nullptr,
                n(5)))),
          n(6));

    auto expected = preorderNodes(root);

    flatten(root);

    check(
        validateFlattened(root, expected),
        "deep right spine in left subtree");

    destroyFlattened(root);
  }

  // Mixed left-only and right-only children.
  {
    TreeNode *root =
        n(10,
          n(5,
            n(2),
            nullptr),
          n(20,
            nullptr,
            n(30,
              n(25),
              nullptr)));

    auto expected = preorderNodes(root);

    flatten(root);

    check(
        validateFlattened(root, expected),
        "mixed one-child nodes");

    destroyFlattened(root);
  }

  // Duplicate values: validation must be by node identity,
  // not just value sequence.
  {
    TreeNode *root =
        n(1,
          n(1,
            n(1),
            nullptr),
          n(1));

    auto expected = preorderNodes(root);

    flatten(root);

    check(
        validateFlattened(root, expected),
        "duplicate values preserve node order");

    destroyFlattened(root);
  }

  // Larger tree to catch lost subtrees.
  {
    TreeNode *root =
        n(8,
          n(4,
            n(2,
              n(1),
              n(3)),
            n(6,
              n(5),
              n(7))),
          n(12,
            n(10,
              n(9),
              n(11)),
            n(14,
              n(13),
              n(15))));

    auto expected = preorderNodes(root);

    flatten(root);

    check(
        validateFlattened(root, expected),
        "larger complete tree");

    destroyFlattened(root);
  }

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
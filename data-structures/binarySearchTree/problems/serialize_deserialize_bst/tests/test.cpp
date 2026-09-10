#include "../../../../../test_protocol.hpp"
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

  cout << (ok ? "PASS " : "FAIL ") << name << '\n';

  string input = string("{\"test\":\"") + name + "\"}";

  dsa_test::emit_case(
      input,
      "true",
      ok ? "true" : "false",
      ok);
}

TreeNode *n(int v, TreeNode *l = nullptr, TreeNode *r = nullptr) {
  auto *node = new TreeNode(v);
  node->left = l;
  node->right = r;
  return node;
}

void destroy(TreeNode *root) {
  if (!root)
    return;

  destroy(root->left);
  destroy(root->right);
  delete root;
}

vector<int> inorder(TreeNode *root) {
  if (!root)
    return {};

  auto left = inorder(root->left);
  auto right = inorder(root->right);

  left.push_back(root->val);
  left.insert(left.end(), right.begin(), right.end());

  return left;
}

bool sameInorder(TreeNode *a, TreeNode *b) {
  return inorder(a) == inorder(b);
}

int main() {
  // Empty tree.
  {
    string s = serializeBST(nullptr);

    check(
        s.empty() &&
            deserializeBST(s) == nullptr,
        "empty tree round trip");
  }

  // Single node.
  {
    TreeNode *root = n(42);
    string s = serializeBST(root);
    TreeNode *copy = deserializeBST(s);

    check(
        s == "42" &&
            sameInorder(root, copy) &&
            copy != nullptr &&
            copy->left == nullptr &&
            copy->right == nullptr &&
            copy->val == 42,
        "single node");
    
    destroy(root);
    destroy(copy);
  }

  // Balanced BST.
  {
    TreeNode *root =
        n(8,
          n(3, n(1), n(6, n(4), n(7))),
          n(10, nullptr, n(14)));

    string s = serializeBST(root);
    TreeNode *copy = deserializeBST(s);

    check(
        sameInorder(root, copy) &&
            s == "8 3 1 6 4 7 10 14",
        "balanced BST round trip");

    destroy(root);
    destroy(copy);
  }

  // Left-skewed tree.
  {
    TreeNode *root =
        n(5,
          n(4,
            n(3,
              n(2,
                n(1)))),
          nullptr);

    string s = serializeBST(root);
    TreeNode *copy = deserializeBST(s);

    check(
        sameInorder(root, copy) &&
            inorder(copy) == vector<int>({1, 2, 3, 4, 5}),
        "left skewed tree");

    destroy(root);
    destroy(copy);
  }

  // Right-skewed tree.
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

    string s = serializeBST(root);
    TreeNode *copy = deserializeBST(s);

    check(
        sameInorder(root, copy) &&
            inorder(copy) == vector<int>({1, 2, 3, 4, 5}),
        "right skewed tree");

    destroy(root);
    destroy(copy);
  }

  // Negative values.
  {
    TreeNode *root =
        n(-2,
          n(-7, n(-10), n(-5)),
          n(3, n(0), n(8)));

    string s = serializeBST(root);
    TreeNode *copy = deserializeBST(s);

    check(
        sameInorder(root, copy) &&
            inorder(copy) ==
                vector<int>({-10, -7, -5, -2, 0, 3, 8}),
        "negative keys");

    destroy(root);
    destroy(copy);
  }

  // INT_MIN and INT_MAX.
  {
    TreeNode *root =
        n(0,
          n(INT_MIN),
          n(INT_MAX));

    string s = serializeBST(root);
    TreeNode *copy = deserializeBST(s);

    check(
        sameInorder(root, copy) &&
            inorder(copy) ==
                vector<int>({INT_MIN, 0, INT_MAX}),
        "extreme integer keys");

    destroy(root);
    destroy(copy);
  }

  // Root with only a left subtree.
  {
    TreeNode *root =
        n(10,
          n(5,
            n(2),
            n(7)),
          nullptr);

    string s = serializeBST(root);
    TreeNode *copy = deserializeBST(s);

    check(
        sameInorder(root, copy) &&
            inorder(copy) == vector<int>({2, 5, 7, 10}),
        "only left subtree");

    destroy(root);
    destroy(copy);
  }

  // Root with only a right subtree.
  {
    TreeNode *root =
        n(10,
          nullptr,
          n(15,
            n(12),
            n(20)));

    string s = serializeBST(root);
    TreeNode *copy = deserializeBST(s);

    check(
        sameInorder(root, copy) &&
            inorder(copy) == vector<int>({10, 12, 15, 20}),
        "only right subtree");

    destroy(root);
    destroy(copy);
  }

  // Important preorder-boundary case:
  // after finishing 2's subtree, 6 belongs to 5's right subtree.
  {
    TreeNode *root =
        n(8,
          n(5,
            n(2,
              nullptr,
              n(3)),
            n(7)),
          n(10,
            n(9),
            n(12)));

    string s = serializeBST(root);
    TreeNode *copy = deserializeBST(s);

    check(
        s == "8 5 2 3 7 10 9 12" &&
            sameInorder(root, copy),
        "preorder subtree boundary handling");

    destroy(root);
    destroy(copy);
  }

  // Another important case where a value doesn't belong
  // to the current subtree but does belong to an ancestor.
  {
    TreeNode *root =
        n(20,
          n(10,
            n(5),
            n(15,
              n(12),
              n(18))),
          n(30,
            n(25),
            n(40)));

    string s = serializeBST(root);
    TreeNode *copy = deserializeBST(s);

    check(
        s == "20 10 5 15 12 18 30 25 40" &&
            sameInorder(root, copy),
        "nested preorder bounds");

    destroy(root);
    destroy(copy);
  }

  // Serialization should contain values only, no null markers.
  {
    TreeNode *root =
        n(4,
          n(2, n(1), n(3)),
          n(6, n(5), n(7)));

    string s = serializeBST(root);

    check(
        s == "4 2 1 3 6 5 7" &&
            s.find("null") == string::npos &&
            s.find("#") == string::npos,
        "compact serialization");

    destroy(root);
  }

  // Deserialized tree should be structurally equivalent,
  // not merely have the same set of values.
  {
    TreeNode *root =
        n(5,
          n(3, n(1), n(4)),
          n(8, nullptr, n(10)));

    string s = serializeBST(root);
    TreeNode *copy = deserializeBST(s);

    bool structureOK =
        copy != nullptr &&
        copy->val == 5 &&
        copy->left != nullptr &&
        copy->left->val == 3 &&
        copy->left->left != nullptr &&
        copy->left->left->val == 1 &&
        copy->left->right != nullptr &&
        copy->left->right->val == 4 &&
        copy->right != nullptr &&
        copy->right->val == 8 &&
        copy->right->left == nullptr &&
        copy->right->right != nullptr &&
        copy->right->right->val == 10;

    check(
        structureOK,
        "preserves BST structure");

    destroy(root);
    destroy(copy);
  }

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}

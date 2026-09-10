#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

static TreeNode *node(int v,
                      TreeNode *l = nullptr,
                      TreeNode *r = nullptr) {
  auto *n = new TreeNode(v);
  n->left = l;
  n->right = r;
  return n;
}

static void destroy(TreeNode *r) {
  if (!r)
    return;

  destroy(r->left);
  destroy(r->right);
  delete r;
}

static vector<int> collect(BSTIterator &it) {
  vector<int> out;

  while (it.hasNext())
    out.push_back(it.next());

  return out;
}

int main() {
  int passed = 0;
  int total = 0;

  auto check = [&](bool ok, const char *name) {
    ++total;
    if (ok)
      ++passed;

    cout << (ok ? "PASS " : "FAIL ")
         << name << '\n';

    cout << "DSA_CASE {\"input\":{\"test\":\""
         << name
         << "\"},\"expected\":true,\"actual\":"
         << (ok ? "true" : "false")
         << ",\"passed\":"
         << (ok ? "true" : "false")
         << "}\n";
  };

  // Balanced BST.
  {
    TreeNode *root =
        node(7,
             node(3, node(1), node(5)),
             node(10, nullptr, node(12)));

    BSTIterator it(root);

    check(
        collect(it) == vector<int>({1, 3, 5, 7, 10, 12}),
        "balanced BST");

    check(
        !it.hasNext(),
        "iterator exhausted after traversal");

    destroy(root);
  }

  // Empty tree.
  {
    BSTIterator it(nullptr);

    check(
        !it.hasNext(),
        "empty tree");
  }

  // Single node.
  {
    TreeNode *root = node(42);
    BSTIterator it(root);

    check(
        it.hasNext() &&
            it.next() == 42 &&
            !it.hasNext(),
        "single node");

    destroy(root);
  }

  // Completely left-skewed tree.
  {
    TreeNode *root =
        node(5,
             node(4,
                  node(3,
                       node(2,
                            node(1)))));

    BSTIterator it(root);

    check(
        collect(it) == vector<int>({1, 2, 3, 4, 5}),
        "left skewed BST");

    destroy(root);
  }

  // Completely right-skewed tree.
  {
    TreeNode *root =
        node(1,
             nullptr,
             node(2,
                  nullptr,
                  node(3,
                       nullptr,
                       node(4,
                            nullptr,
                            node(5)))));

    BSTIterator it(root);

    check(
        collect(it) == vector<int>({1, 2, 3, 4, 5}),
        "right skewed BST");

    destroy(root);
  }

  // Negative values.
  {
    TreeNode *root =
        node(0,
             node(-5, node(-10), node(-2)),
             node(7, node(3), node(9)));

    BSTIterator it(root);

    check(
        collect(it) ==
            vector<int>({-10, -5, -2, 0, 3, 7, 9}),
        "negative and positive values");

    destroy(root);
  }

  // Integer extremes.
  {
    TreeNode *root =
        node(0,
             node(INT_MIN),
             node(INT_MAX));

    BSTIterator it(root);

    check(
        collect(it) ==
            vector<int>({INT_MIN, 0, INT_MAX}),
        "integer extremes");

    destroy(root);
  }

  // Important: two iterators must be independent.
  // This catches a static/shared stack bug.
  {
    TreeNode *root1 =
        node(2, node(1), node(3));

    TreeNode *root2 =
        node(20, node(10), node(30));

    BSTIterator it1(root1);
    BSTIterator it2(root2);

    bool ok =
        it1.next() == 1 &&
        it2.next() == 10 &&
        it1.next() == 2 &&
        it2.next() == 20 &&
        it1.next() == 3 &&
        it2.next() == 30 &&
        !it1.hasNext() &&
        !it2.hasNext();

    check(
        ok,
        "multiple iterator instances are independent");

    destroy(root1);
    destroy(root2);
  }

  // Check hasNext without advancing.
  {
    TreeNode *root =
        node(2, node(1), node(3));

    BSTIterator it(root);

    bool ok =
        it.hasNext() &&
        it.hasNext() &&
        it.next() == 1 &&
        it.hasNext() &&
        it.hasNext() &&
        it.next() == 2 &&
        it.hasNext() &&
        it.next() == 3 &&
        !it.hasNext();

    check(
        ok,
        "hasNext does not advance iterator");

    destroy(root);
  }

  // More irregular tree shape.
  {
    TreeNode *root =
        node(8,
             node(3,
                  node(1),
                  node(6,
                       node(4),
                       node(7))),
             node(10,
                  nullptr,
                  node(14,
                       node(13),
                       nullptr)));

    BSTIterator it(root);

    check(
        collect(it) ==
            vector<int>({1, 3, 4, 6, 7, 8, 10, 13, 14}),
        "irregular BST");

    destroy(root);
  }

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
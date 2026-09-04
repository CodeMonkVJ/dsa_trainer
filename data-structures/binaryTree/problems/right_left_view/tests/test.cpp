#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int main() {
  int passed = 0;
  int total = 0;

  auto vec2str = [](const vector<int> &v) {
    ostringstream out;
    out << '[';
    for (size_t i = 0; i < v.size(); ++i) {
      if (i)
        out << ',';
      out << v[i];
    }
    out << ']';
    return out.str();
  };

  auto check = [&](const string &treeDesc,
                   const string &view,
                   TreeNode *root,
                   const vector<int> &expected,
                   bool isLeft) {
    vector<int> actual = isLeft ? leftView(root) : rightView(root);
    bool ok = actual == expected;

    ++total;
    if (ok)
      ++passed;

    dsa_test::emit_case(
        "{\"tree\":" + treeDesc + ",\"view\":\"" + view + "\"}",
        vec2str(expected),
        vec2str(actual),
        ok);
  };

  // empty tree
  check("null", "left", nullptr, {}, true);
  check("null", "right", nullptr, {}, false);

  // single node
  {
    TreeNode root{1, nullptr, nullptr};

    check("[1]", "left", &root, {1}, true);
    check("[1]", "right", &root, {1}, false);
  }

  // normal uneven tree
  {
    TreeNode a{4, nullptr, nullptr};
    TreeNode b{5, nullptr, nullptr};
    TreeNode l{2, &a, nullptr};
    TreeNode r{3, nullptr, &b};
    TreeNode root{1, &l, &r};

    check("[1,2,3,4,null,null,5]",
          "left", &root, {1, 2, 4}, true);

    check("[1,2,3,4,null,null,5]",
          "right", &root, {1, 3, 5}, false);
  }

  // left-skewed tree
  {
    TreeNode d{4, nullptr, nullptr};
    TreeNode c{3, &d, nullptr};
    TreeNode b{2, &c, nullptr};
    TreeNode root{1, &b, nullptr};

    check("[1,2,null,3,null,4]",
          "left", &root, {1, 2, 3, 4}, true);

    check("[1,2,null,3,null,4]",
          "right", &root, {1, 2, 3, 4}, false);
  }

  // right-skewed tree
  {
    TreeNode d{4, nullptr, nullptr};
    TreeNode c{3, nullptr, &d};
    TreeNode b{2, nullptr, &c};
    TreeNode root{1, nullptr, &b};

    check("[1,null,2,null,3,null,4]",
          "left", &root, {1, 2, 3, 4}, true);

    check("[1,null,2,null,3,null,4]",
          "right", &root, {1, 2, 3, 4}, false);
  }

  // deeper uneven tree
  {
    TreeNode g{7, nullptr, nullptr};
    TreeNode f{6, nullptr, nullptr};
    TreeNode e{5, nullptr, &g};
    TreeNode d{4, nullptr, nullptr};

    TreeNode l{2, &d, &e};
    TreeNode r{3, nullptr, &f};
    TreeNode root{1, &l, &r};

    check("[1,2,3,4,5,null,6,null,null,null,7]",
          "left", &root, {1, 2, 4, 7}, true);

    check("[1,2,3,4,5,null,6,null,null,null,7]",
          "right", &root, {1, 3, 6, 7}, false);
  }

  // visible node can come from an inner branch
  {
    TreeNode x{6, nullptr, nullptr};
    TreeNode l{2, nullptr, &x};
    TreeNode r{3, nullptr, nullptr};
    TreeNode root{1, &l, &r};

    check("[1,2,3,null,6]",
          "left", &root, {1, 2, 6}, true);

    check("[1,2,3,null,6]",
          "right", &root, {1, 3, 6}, false);
  }

  // duplicate values should not matter
  {
    TreeNode a{2, nullptr, nullptr};
    TreeNode b{2, nullptr, nullptr};
    TreeNode l{1, &a, nullptr};
    TreeNode r{1, nullptr, &b};
    TreeNode root{1, &l, &r};

    check("[1,1,1,2,null,null,2]",
          "left", &root, {1, 1, 2}, true);

    check("[1,1,1,2,null,null,2]",
          "right", &root, {1, 1, 2}, false);
  }

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
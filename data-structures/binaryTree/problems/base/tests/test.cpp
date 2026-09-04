#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int main() {
  int passed = 0;
  int total = 0;

  auto vec2str = [](const vector<vector<int>>& x) {
    ostringstream actual;
    actual << '[';
    for (size_t i = 0; i < x.size(); ++i) {
      if (i)
        actual << ',';

      actual << '[';
      for (size_t j = 0; j < x[i].size(); ++j) {
        if (j)
          actual << ',';
        actual << x[i][j];
      }
      actual << ']';
    }
    actual << ']';
    return actual.str();
  };

  auto record = [&](const string& input,
                    const string& expected,
                    const vector<vector<int>>& actual,
                    bool ok) {
    dsa_test::emit_case(input, expected, vec2str(actual), ok);

    ++total;
    if (ok)
      ++passed;
  };

  // empty tree
  {
    auto x = levelOrder(nullptr);
    bool ok = x.empty();

    record(
        "{\"tree\":[]}",
        "[]",
        x,
        ok);
  }

  // single node
  {
    TreeNode a{1, nullptr, nullptr};

    auto x = levelOrder(&a);
    bool ok = x == vector<vector<int>>{{1}};

    record(
        "{\"tree\":[1]}",
        "[[1]]",
        x,
        ok);
  }

  // simple full tree
  {
    TreeNode c{3, nullptr, nullptr};
    TreeNode b{2, nullptr, nullptr};
    TreeNode a{1, &b, &c};

    auto x = levelOrder(&a);
    bool ok = x == vector<vector<int>>{{1}, {2, 3}};

    record(
        "{\"tree\":[1,2,3]}",
        "[[1],[2,3]]",
        x,
        ok);
  }

  // left-skewed tree
  {
    TreeNode d{4, nullptr, nullptr};
    TreeNode c{3, &d, nullptr};
    TreeNode b{2, &c, nullptr};
    TreeNode a{1, &b, nullptr};

    auto x = levelOrder(&a);
    bool ok = x == vector<vector<int>>{{1}, {2}, {3}, {4}};

    record(
        "{\"tree\":[1,2,null,3,null,4]}",
        "[[1],[2],[3],[4]]",
        x,
        ok);
  }

  // right-skewed tree
  {
    TreeNode d{4, nullptr, nullptr};
    TreeNode c{3, nullptr, &d};
    TreeNode b{2, nullptr, &c};
    TreeNode a{1, nullptr, &b};

    auto x = levelOrder(&a);
    bool ok = x == vector<vector<int>>{{1}, {2}, {3}, {4}};

    record(
        "{\"tree\":[1,null,2,null,3,null,4]}",
        "[[1],[2],[3],[4]]",
        x,
        ok);
  }

  // uneven tree
  {
    TreeNode f{6, nullptr, nullptr};
    TreeNode e{5, nullptr, nullptr};
    TreeNode d{4, nullptr, nullptr};

    TreeNode c{3, nullptr, &f};
    TreeNode b{2, &d, &e};
    TreeNode a{1, &b, &c};

    auto x = levelOrder(&a);
    bool ok = x == vector<vector<int>>{{1}, {2, 3}, {4, 5, 6}};

    record(
        "{\"tree\":[1,2,3,4,5,null,6]}",
        "[[1],[2,3],[4,5,6]]",
        x,
        ok);
  }

  // deeper uneven tree
  {
    TreeNode g{7, nullptr, nullptr};
    TreeNode f{6, nullptr, nullptr};
    TreeNode e{5, nullptr, &g};
    TreeNode d{4, nullptr, nullptr};

    TreeNode c{3, nullptr, &f};
    TreeNode b{2, &d, &e};
    TreeNode a{1, &b, &c};

    auto x = levelOrder(&a);
    bool ok =
        x == vector<vector<int>>{{1}, {2, 3}, {4, 5, 6}, {7}};

    record(
        "{\"tree\":[1,2,3,4,5,null,6,null,null,null,7]}",
        "[[1],[2,3],[4,5,6],[7]]",
        x,
        ok);
  }

  // duplicate values
  {
    TreeNode d{2, nullptr, nullptr};
    TreeNode c{1, nullptr, nullptr};
    TreeNode b{1, &d, nullptr};
    TreeNode a{1, &b, &c};

    auto x = levelOrder(&a);
    bool ok = x == vector<vector<int>>{{1}, {1, 1}, {2}};

    record(
        "{\"tree\":[1,1,1,2]}",
        "[[1],[1,1],[2]]",
        x,
        ok);
  }

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
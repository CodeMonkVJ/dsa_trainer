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
}

void sortVec(vector<int> &v) {
  sort(v.begin(), v.end());
}

int main() {
  /*
          3
         / \
        5   1
       / \ / \
      6  2 0  8
        / \
       7   4
  */

  TreeNode a(3), b(5), c(1), d(6), e(2),
           f(0), g(8), h(7), i(4);

  a.left = &b;
  a.right = &c;

  b.left = &d;
  b.right = &e;

  c.left = &f;
  c.right = &g;

  e.left = &h;
  e.right = &i;

  {
    auto x = nodesAtDistanceK(&a, 5, 2);
    sortVec(x);

    check(
        x == vector<int>({1, 4, 7}),
        "distance two from internal target");
  }

  {
    auto x = nodesAtDistanceK(&a, 5, 1);
    sortVec(x);

    check(
        x == vector<int>({2, 3, 6}),
        "distance one includes parent and children");
  }

  {
    auto x = nodesAtDistanceK(&a, 3, 0);

    check(
        x == vector<int>({3}),
        "target itself");
  }

  {
    auto x = nodesAtDistanceK(&a, 3, 1);
    sortVec(x);

    check(
        x == vector<int>({1, 5}),
        "distance one from root");
  }

  {
    auto x = nodesAtDistanceK(&a, 3, 2);
    sortVec(x);

    check(
        x == vector<int>({0, 2, 6, 8}),
        "distance two from root");
  }

  {
    auto x = nodesAtDistanceK(&a, 7, 1);
    sortVec(x);

    check(
        x == vector<int>({2}),
        "leaf target distance one");
  }

  {
    auto x = nodesAtDistanceK(&a, 7, 2);
    sortVec(x);

    check(
        x == vector<int>({4, 5}),
        "leaf target distance two");
  }

  {
    auto x = nodesAtDistanceK(&a, 7, 3);
    sortVec(x);

    check(
        x == vector<int>({3, 6}),
        "leaf target moves upward through ancestors");
  }

  {
    auto x = nodesAtDistanceK(&a, 7, 4);
    sortVec(x);

    check(
        x == vector<int>({1}),
        "crosses root into opposite subtree");
  }

  {
    auto x = nodesAtDistanceK(&a, 7, 5);
    sortVec(x);

    check(
        x == vector<int>({0, 8}),
        "deep cross subtree distance");
  }

  {
    auto x = nodesAtDistanceK(&a, 7, 6);

    check(
        x.empty(),
        "distance larger than reachable depth");
  }

  {
    auto x = nodesAtDistanceK(&a, 42, 2);

    check(
        x.empty(),
        "missing target");
  }

  {
    auto x = nodesAtDistanceK(&a, 5, -1);

    check(
        x.empty(),
        "negative distance");
  }

  {
    TreeNode single(10);

    auto x = nodesAtDistanceK(&single, 10, 0);

    check(
        x == vector<int>({10}),
        "single node distance zero");
  }

  {
    TreeNode single(10);

    auto x = nodesAtDistanceK(&single, 10, 1);

    check(
        x.empty(),
        "single node positive distance");
  }

  {
    check(
        nodesAtDistanceK(nullptr, 1, 0).empty(),
        "empty tree");
  }

  /*
      1
       \
        2
         \
          3
           \
            4
  */
  {
    TreeNode p(1), q(2), r(3), s(4);

    p.right = &q;
    q.right = &r;
    r.right = &s;

    auto x = nodesAtDistanceK(&p, 3, 2);
    sortVec(x);

    check(
        x == vector<int>({1}),
        "right skewed tree");
  }

  /*
          10
         /
        5
       /
      2
     /
    1
  */
  {
    TreeNode p(10), q(5), r(2), s(1);

    p.left = &q;
    q.left = &r;
    r.left = &s;

    auto x = nodesAtDistanceK(&p, 2, 2);
    sortVec(x);

    check(
        x == vector<int>({10}),
        "left skewed tree");
  }

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
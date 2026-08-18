#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool x, const char *n) {
  ++total;
  if (x)
    ++passed;
  string input = "{\"case\":\"" + string(n) + "\"}";
  dsa_test::emit_case(input, "true", x ? "true" : "false", x);
}
void pre(TreeNode *n, vector<int> &o) {
  if (n) {
    o.push_back(n->val);
    pre(n->left, o);
    pre(n->right, o);
  }
}
void in(TreeNode *n, vector<int> &o) {
  if (n) {
    in(n->left, o);
    o.push_back(n->val);
    in(n->right, o);
  }
}
int main() {
  auto *a = buildTree({3, 9, 20, 15, 7}, {9, 3, 15, 20, 7});
  vector<int> p, i;
  pre(a, p);
  in(a, i);
  check(p == vector<int>({3, 9, 20, 15, 7}) &&
            i == vector<int>({9, 3, 15, 20, 7}),
        "reconstruct tree");
  check(buildTree({}, {}) == nullptr, "empty input");
  auto *b = buildTree({1, 2, 3}, {3, 2, 1});
  p.clear();
  i.clear();
  in(b, i);
  check(i == vector<int>({3, 2, 1}), "skewed tree");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

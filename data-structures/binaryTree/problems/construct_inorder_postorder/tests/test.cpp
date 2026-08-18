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
void post(TreeNode *n, vector<int> &o) {
  if (n) {
    post(n->left, o);
    post(n->right, o);
    o.push_back(n->val);
  }
}
int main() {
  auto *n = buildTree({9, 3, 15, 20, 7}, {9, 15, 7, 20, 3});
  vector<int> p, q;
  pre(n, p);
  post(n, q);
  check(p == vector<int>({3, 9, 20, 15, 7}) &&
            q == vector<int>({9, 15, 7, 20, 3}),
        "reconstruct tree");
  check(buildTree({}, {}) == nullptr, "empty input");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

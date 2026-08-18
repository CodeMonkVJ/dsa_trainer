#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  auto *r = new TreeNode(1);
  r->left = new TreeNode(2);
  r->right = new TreeNode(3);
  r->left->right = new TreeNode(5);
  int p = 0, t = 0;
  auto ck = [&](bool x, const char *input) {
    ++t;
    p += x;
    dsa_test::emit_case(input, "true", x ? "true" : "false", x);
  };
  ck(iterativePreorder(nullptr) == vector<int>{},
     "{\"tree\":null,\"traversal\":\"iterative_preorder\"}");
  ck(iterativePreorder(r) == vector<int>({1, 2, 5, 3}),
     "{\"tree\":[1,2,3,null,5],\"traversal\":\"iterative_preorder\"}");
  cout << "DSA_RESULT {\"passed\":" << p << ",\"total\":" << t << "}\n";
  return p != t;
}

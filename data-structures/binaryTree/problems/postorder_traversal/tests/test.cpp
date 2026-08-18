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
  ck(postorderTraversal(nullptr) == vector<int>{},
     "{\"tree\":null,\"traversal\":\"postorder\"}");
  ck(postorderTraversal(r) == vector<int>({5, 2, 3, 1}),
     "{\"tree\":[1,2,3,null,5],\"traversal\":\"postorder\"}");
  cout << "DSA_RESULT {\"passed\":" << p << ",\"total\":" << t << "}\n";
  return p != t;
}

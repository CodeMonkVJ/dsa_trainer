#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  auto *r = new TreeNode(4);
  r->left = new TreeNode(2);
  r->right = new TreeNode(6);
  r->left->left = new TreeNode(1);
  r->left->right = new TreeNode(3);
  int p = 0, t = 0;
  auto ck = [&](bool x, const char *input) {
    ++t;
    p += x;
    dsa_test::emit_case(input, "true", x ? "true" : "false", x);
  };
  ck(iterativeInorder(nullptr) == vector<int>{},
     "{\"tree\":null,\"traversal\":\"iterative_inorder\"}");
  ck(iterativeInorder(r) == vector<int>({1, 2, 3, 4, 6}),
     "{\"tree\":[4,2,6,1,3],\"traversal\":\"iterative_inorder\"}");
  cout << "DSA_RESULT {\"passed\":" << p << ",\"total\":" << t << "}\n";
  return p != t;
}

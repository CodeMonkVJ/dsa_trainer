#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char *name) {
  ++total;
  if (ok)
    ++passed;
  string input = "{\"case\":\"" + string(name) + "\"}";
  dsa_test::emit_case(input, "true", ok ? "true" : "false", ok);
}
TreeNode *sample() {
  auto *n = new TreeNode(1);
  n->left = new TreeNode(2);
  n->right = new TreeNode(3);
  n->right->left = new TreeNode(4);
  return n;
}
int main() {
  check(areIdentical(nullptr, nullptr), "two empty trees");
  TreeNode *a = sample();
  TreeNode *b = sample();
  check(areIdentical(a, b), "same structure and values");
  b->right->left->val = 9;
  check(!areIdentical(a, b), "different value");
  b = sample();
  b->right->left = nullptr;
  check(!areIdentical(a, b), "different structure");
  check(!areIdentical(a, nullptr), "one empty tree");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

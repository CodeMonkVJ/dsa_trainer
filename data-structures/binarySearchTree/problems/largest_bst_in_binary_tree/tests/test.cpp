#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool x, const char *s) {
  ++total;
  if (x)
    ++passed;
  cout << "DSA_CASE {\"input\":{\"case\":\"" << s
       << "\"},\"expected\":true,\"actual\":" << (x ? "true" : "false")
       << ",\"passed\":" << (x ? "true" : "false") << "}\n";
}
TreeNode *n(int v, TreeNode *l = nullptr, TreeNode *r = nullptr) {
  auto *x = new TreeNode(v);
  x->left = l;
  x->right = r;
  return x;
}
int main() {
  check(largestBST(n(10, n(5, n(1), n(8)), n(15, n(7), n(20)))) == 3,
        "finds largest valid subtree");
  check(largestBST(n(5, n(2), n(8))) == 3, "recognizes an entire BST");
  check(largestBST(n(5, n(6), n(4))) == 1, "handles invalid root");
  check(largestBST(nullptr) == 0, "handles empty tree");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

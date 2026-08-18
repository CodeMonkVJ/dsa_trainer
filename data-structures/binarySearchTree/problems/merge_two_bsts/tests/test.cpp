#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char *n) {
  ++total;
  if (ok)
    ++passed;
  cout << "DSA_CASE {\"input\":{\"case\":\"" << n
       << "\"},\"expected\":true,\"actual\":" << (ok ? "true" : "false")
       << ",\"passed\":" << (ok ? "true" : "false") << "}\n";
}
TreeNode *n(int v, TreeNode *l = nullptr, TreeNode *r = nullptr) {
  auto *x = new TreeNode(v);
  x->left = l;
  x->right = r;
  return x;
}
int main() {
  TreeNode *a = n(3, n(1), n(5));
  TreeNode *b = n(4, n(2), n(6));
  check(mergeBSTs(a, b) == vector<int>({1, 2, 3, 4, 5, 6}),
        "merges two disjoint trees");
  TreeNode *c = n(2, n(1), n(3));
  TreeNode *d = n(2, n(0), n(4));
  check(mergeBSTs(c, d) == vector<int>({0, 1, 2, 2, 3, 4}),
        "preserves shared keys from both trees");
  check(mergeBSTs(nullptr, nullptr).empty(), "handles empty trees");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

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
vector<int> in(TreeNode *x) {
  if (!x)
    return {};
  auto a = in(x->left), b = in(x->right);
  a.push_back(x->val);
  a.insert(a.end(), b.begin(), b.end());
  return a;
}
int height(TreeNode *x) {
  return x ? 1 + max(height(x->left), height(x->right)) : 0;
}
int main() {
  auto *t = constructBST({1, 2, 3, 4, 5, 6, 7});
  check(in(t) == vector<int>({1, 2, 3, 4, 5, 6, 7}), "preserves sorted keys");
  check(height(t) <= 3, "constructs a balanced tree");
  check(constructBST({}) == nullptr, "handles empty input");
  auto *u = constructBST({-3, -1, 4});
  check(in(u) == vector<int>({-3, -1, 4}), "supports negative keys");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

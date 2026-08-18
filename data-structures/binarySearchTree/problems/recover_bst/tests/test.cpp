#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char *s) {
  ++total;
  if (ok)
    ++passed;
  cout << "DSA_CASE {\"input\":{\"case\":\"" << s
       << "\"},\"expected\":true,\"actual\":" << (ok ? "true" : "false")
       << ",\"passed\":" << (ok ? "true" : "false") << "}\n";
}
TreeNode *n(int v, TreeNode *l = nullptr, TreeNode *r = nullptr) {
  auto *x = new TreeNode(v);
  x->left = l;
  x->right = r;
  return x;
}
vector<int> in(TreeNode *x) {
  if (!x)
    return {};
  auto a = in(x->left), b = in(x->right);
  a.push_back(x->val);
  a.insert(a.end(), b.begin(), b.end());
  return a;
}
int main() {
  auto *t = n(3, n(1), n(4, n(2), nullptr));
  recoverBST(t);
  check(in(t) == vector<int>({1, 2, 3, 4}), "recovers non-adjacent swap");
  auto *u = n(2, n(3), n(1));
  recoverBST(u);
  check(in(u) == vector<int>({1, 2, 3}), "recovers adjacent swap");
  recoverBST(nullptr);
  check(true, "handles empty tree");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

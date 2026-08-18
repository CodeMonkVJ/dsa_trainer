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
vector<int> in(TreeNode *x) {
  if (!x)
    return {};
  auto a = in(x->left), b = in(x->right);
  a.push_back(x->val);
  a.insert(a.end(), b.begin(), b.end());
  return a;
}
int main() {
  auto *t = n(8, n(3, n(1), n(6, n(4), n(7))), n(10, nullptr, n(14)));
  string s = serializeBST(t);
  check(in(deserializeBST(s)) == in(t), "round-trips a BST");
  check(deserializeBST(serializeBST(nullptr)) == nullptr,
        "round-trips empty tree");
  auto *u = deserializeBST("0 -5 -10 5 3");
  check(in(u) == vector<int>({-10, -5, 0, 3, 5}), "supports negative keys");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

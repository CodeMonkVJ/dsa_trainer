#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
static void preorder(TreeNode *r, vector<int> *out) {
  if (!r)
    return;
  out->push_back(r->value);
  preorder(r->left, out);
  preorder(r->right, out);
}
static bool validBST(TreeNode *r, long long lo, long long hi) {
  return !r ||
         (r->value > lo && r->value < hi && validBST(r->left, lo, r->value) &&
          validBST(r->right, r->value, hi));
}
static void destroy(TreeNode *r) {
  if (!r)
    return;
  destroy(r->left);
  destroy(r->right);
  delete r;
}
int main() {
  int passed = 0, total = 0;
  auto check = [&](bool ok) {
    ++total;
    passed += ok;
    cout << "DSA_CASE {\"input\":{\"case\":" << total
         << "},\"expected\":true,\"actual\":" << (ok ? "true" : "false")
         << ",\"passed\":" << (ok ? "true" : "false") << "}\n";
  };
  for (const auto &values :
       {vector<int>{8, 5, 1, 7, 10, 12}, vector<int>{4, 2, 1, 3, 6, 5, 7},
        vector<int>{5}, vector<int>{}}) {
    TreeNode *root = constructBST(values);
    vector<int> got;
    preorder(root, &got);
    check(got == values);
    check(validBST(root, LLONG_MIN, LLONG_MAX));
    destroy(root);
  }
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed != total;
}

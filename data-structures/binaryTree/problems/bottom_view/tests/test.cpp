#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  TreeNode a{4, nullptr, nullptr}, b{5, nullptr, nullptr}, l{2, &a, nullptr},
      r{3, nullptr, &b}, root{1, &l, &r};
  bool ok = bottomView(&root) == vector<int>({4, 2, 1, 3, 5}) &&
            bottomView(nullptr).empty();
  auto actual = bottomView(&root);
  ostringstream out;
  out << '[';
  for (size_t i = 0; i < actual.size(); ++i) {
    if (i)
      out << ',';
    out << actual[i];
  }
  out << ']';
  dsa_test::emit_case("{\"tree\":[1,2,3,4,null,null,5]}", "[4,2,1,3,5]",
                      out.str(), actual == vector<int>({4, 2, 1, 3, 5}));
  dsa_test::emit_case("{\"tree\":null}", "[]", "[]",
                      bottomView(nullptr).empty());
  cout << "DSA_RESULT {\"passed\":" << (ok ? 2 : 0) << ",\"total\":2}\n";
  return ok ? 0 : 1;
}

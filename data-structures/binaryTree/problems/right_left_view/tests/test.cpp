#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  TreeNode a{4, nullptr, nullptr}, b{5, nullptr, nullptr}, l{2, &a, nullptr},
      r{3, nullptr, &b}, root{1, &l, &r};
  auto lj = leftView(&root), rj = rightView(&root);
  bool lok = lj == vector<int>({1, 2, 4}), rok = rj == vector<int>({1, 3, 5}),
       eok = leftView(nullptr).empty();
  dsa_test::emit_case("{\"tree\":[1,2,3,4,null,null,5],\"view\":\"left\"}",
                      "[1,2,4]", "[1,2,4]", lok);
  dsa_test::emit_case("{\"tree\":[1,2,3,4,null,null,5],\"view\":\"right\"}",
                      "[1,3,5]", "[1,3,5]", rok);
  dsa_test::emit_case("{\"tree\":null,\"view\":\"left\"}", "[]", "[]", eok);
  bool ok = lok && rok && eok;
  cout << "DSA_RESULT {\"passed\":" << (lok + rok + eok) << ",\"total\":3}\n";
  return ok ? 0 : 1;
}

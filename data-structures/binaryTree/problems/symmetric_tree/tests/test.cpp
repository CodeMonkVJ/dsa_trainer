#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  TreeNode a{2, nullptr, nullptr}, b{2, nullptr, nullptr}, l{3, &a, nullptr},
      r{3, nullptr, &b}, root{1, &l, &r};
  TreeNode bad{4, nullptr, nullptr};
  r.right = &bad;
  bool empty_ok = isSymmetric(nullptr), broken_ok = !isSymmetric(&root);
  r.right = &b;
  bool c = isSymmetric(&root);
  dsa_test::emit_case("{\"tree\":null}", "true", empty_ok ? "true" : "false",
                      empty_ok);
  dsa_test::emit_case("{\"tree\":[1,3,3,2,null,null,2,4]}", "true",
                      broken_ok ? "true" : "false", broken_ok);
  dsa_test::emit_case("{\"tree\":[1,3,3,2,null,null,2]}", "true",
                      c ? "true" : "false", c);
  bool ok = empty_ok && broken_ok && c;
  cout << "DSA_RESULT {\"passed\":" << (empty_ok + broken_ok + c)
       << ",\"total\":3}\n";
  return ok ? 0 : 1;
}

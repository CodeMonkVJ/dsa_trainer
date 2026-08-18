#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  TreeNode a(1), b(2), c(3), d(4);
  a.left = &b;
  a.right = &c;
  b.left = &d;
  const bool first_ok = isBalanced(&a);
  dsa_test::emit_case(
      "{\"tree\":{\"root\":1,\"left\":2,\"right\":3,\"left_left\":4}}", "true",
      first_ok ? "true" : "false", first_ok);
  const bool second_ok = isBalanced(nullptr);
  dsa_test::emit_case("{\"tree\":null}", "true", second_ok ? "true" : "false",
                      second_ok);
  TreeNode e(5), f(6);
  d.left = &e;
  e.left = &f;
  const bool third_ok = !isBalanced(&a);
  dsa_test::emit_case("{\"tree\":{\"root\":1,\"left\":2,\"left_left\":4,\"left_"
                      "left_left\":5,\"left_left_left_left\":6}}",
                      "true", third_ok ? "true" : "false", third_ok);
  if (!first_ok || !second_ok || !third_ok)
    return 1;
  cout << "DSA_RESULT {\"passed\":3,\"total\":3}\n";
}

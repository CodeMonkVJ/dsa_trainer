#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  TreeNode n4{4, nullptr, nullptr}, n5{5, nullptr, nullptr},
      n2{2, &n4, nullptr}, n3{3, nullptr, &n5}, r{1, &n2, &n3};
  auto actual = topView(&r);
  bool a = actual == vector<int>({4, 2, 1, 3, 5}), b = topView(nullptr).empty();
  dsa_test::emit_case("{\"tree\":[1,2,3,4,null,null,5]}", "[4,2,1,3,5]",
                      "[4,2,1,3,5]", a);
  dsa_test::emit_case("{\"tree\":null}", "[]", "[]", b);
  bool ok = a && b;
  cout << "DSA_RESULT {\"passed\":" << (a + b) << ",\"total\":2}\n";
  return ok ? 0 : 1;
}

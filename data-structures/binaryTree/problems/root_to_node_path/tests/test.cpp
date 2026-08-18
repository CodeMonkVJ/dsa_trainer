#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  TreeNode a{4, nullptr, nullptr}, b{5, nullptr, nullptr}, l{2, &a, nullptr},
      r{3, nullptr, &b}, root{1, &l, &r};
  auto p4 = rootToNodePath(&root, 4), p5 = rootToNodePath(&root, 5),
       p9 = rootToNodePath(&root, 9);
  bool path4_ok = p4 == vector<int>({1, 2, 4}),
       path5_ok = p5 == vector<int>({1, 3, 5}), missing_ok = p9.empty();
  dsa_test::emit_case("{\"tree\":[1,2,3,4,null,null,5],\"target\":4}",
                      "[1,2,4]", "[1,2,4]", path4_ok);
  dsa_test::emit_case("{\"tree\":[1,2,3,4,null,null,5],\"target\":5}",
                      "[1,3,5]", "[1,3,5]", path5_ok);
  dsa_test::emit_case("{\"tree\":[1,2,3,4,null,null,5],\"target\":9}", "[]",
                      "[]", missing_ok);
  bool ok = path4_ok && path5_ok && missing_ok;
  cout << "DSA_RESULT {\"passed\":" << (path4_ok + path5_ok + missing_ok)
       << ",\"total\":3}\n";
  return ok ? 0 : 1;
}

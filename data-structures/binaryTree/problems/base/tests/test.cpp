#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  TreeNode c{3, nullptr, nullptr}, b{2, nullptr, nullptr}, a{1, &b, &c};
  auto x = levelOrder(&a);
  bool ok = x == vector<vector<int>>{{1}, {2, 3}};
  ostringstream actual;
  actual << '[';
  for (size_t i = 0; i < x.size(); ++i) {
    if (i)
      actual << ',';
    actual << '[';
    for (size_t j = 0; j < x[i].size(); ++j) {
      if (j)
        actual << ',';
      actual << x[i][j];
    }
    actual << ']';
  }
  actual << ']';
  dsa_test::emit_case("{\"tree\":[1,2,3]}", "[[1],[2,3]]", actual.str(), ok);
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}

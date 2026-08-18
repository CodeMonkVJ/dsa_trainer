#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  int actual = minPathSum({{1, 3, 1}, {1, 5, 1}, {4, 2, 1}});
  bool ok = actual == 7;
  dsa_test::emit_case("{\"grid\":[[1,3,1],[1,5,1],[4,2,1]]}", "7",
                      to_string(actual), ok);
  cout << (ok ? "PASS minimum path\n" : "FAIL minimum path\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}

#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  int actual = rodCutting({2, 5, 7, 8, 10}, 5);
  bool ok = actual == 12;
  dsa_test::emit_case("{\"prices\":[2,5,7,8,10],\"length\":5}", "12",
                      to_string(actual), ok);
  cout << (ok ? "PASS rod_cutting\n" : "FAIL rod_cutting\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}

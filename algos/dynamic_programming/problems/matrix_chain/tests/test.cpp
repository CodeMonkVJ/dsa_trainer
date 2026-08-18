#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  int actual = matrixChain({40, 20, 30, 10, 30});
  bool ok = actual == 17000;
  dsa_test::emit_case("{\"dimensions\":[40,20,30,10,30]}", "17000",
                      to_string(actual), ok);
  cout << (ok ? "PASS matrix_chain\n" : "FAIL matrix_chain\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}

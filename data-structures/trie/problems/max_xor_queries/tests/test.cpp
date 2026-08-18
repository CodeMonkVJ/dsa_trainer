#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  bool ok = maxXorQueries({0, 1, 2, 3, 4}, {{3, 1}, {1, 3}, {5, 6}}) ==
            vector<int>({3, 3, 7});
  dsa_test::emit_case("{\"problem\":\"max_xor_queries\"}", "true",
                      ok ? "true" : "false", ok);
  cout << (ok ? "PASS max_xor_queries\n" : "FAIL max_xor_queries\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}

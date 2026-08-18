#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  bool ok = maxXorPair({3, 10, 5, 25, 2, 8}) == 28;
  dsa_test::emit_case("{\"problem\":\"max_xor_pair\"}", "true",
                      ok ? "true" : "false", ok);
  cout << (ok ? "PASS max_xor_pair\n" : "FAIL max_xor_pair\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}

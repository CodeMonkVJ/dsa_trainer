#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  bool ok = powerSet("ab") == vector<string>({"", "a", "ab", "b"});
  dsa_test::emit_case("{\"problem\":\"power_set\"}", "true",
                      ok ? "true" : "false", ok);
  cout << (ok ? "PASS power set\n" : "FAIL power set\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}

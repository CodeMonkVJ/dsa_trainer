#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  int actual = editDistance("horse", "ros");
  bool ok = actual == 3;
  dsa_test::emit_case("{\"first\":\"horse\",\"second\":\"ros\"}", "3",
                      to_string(actual), ok);
  cout << (ok ? "PASS edit_distance\n" : "FAIL edit_distance\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}

#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  bool first = wildcardMatch("adceb", "*a*b"),
       second = wildcardMatch("cb", "?a");
  bool ok = first && !second;
  dsa_test::emit_case("{\"first_text\":\"adceb\",\"first_pattern\":\"*a*b\","
                      "\"second_text\":\"cb\",\"second_pattern\":\"?a\"}",
                      "{\"first\":true,\"second\":false}",
                      "{\"first\":" + string(first ? "true" : "false") +
                          ",\"second\":" + string(second ? "true" : "false") +
                          "}",
                      ok);
  cout << (ok ? "PASS wildcard_matching\n" : "FAIL wildcard_matching\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}

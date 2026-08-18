#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  int actual = distinctSubsequences("rabbbit", "rabbit");
  bool ok = actual == 3;
  dsa_test::emit_case("{\"source\":\"rabbbit\",\"target\":\"rabbit\"}", "3",
                      to_string(actual), ok);
  cout << (ok ? "PASS distinct_subsequences\n"
              : "FAIL distinct_subsequences\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}

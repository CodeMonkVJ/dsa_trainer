#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  int actual = longestCommonSubsequence("abcde", "ace");
  bool ok = actual == 3;
  dsa_test::emit_case("{\"first\":\"abcde\",\"second\":\"ace\"}", "3",
                      to_string(actual), ok);
  cout << (ok ? "PASS lcs\n" : "FAIL lcs\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}

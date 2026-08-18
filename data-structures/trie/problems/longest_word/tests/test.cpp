#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  bool ok =
      longestWord({"n", "ni", "nin", "ninj", "ninja", "ninga"}) == "ninja";
  dsa_test::emit_case("{\"problem\":\"longest_word\"}", "true",
                      ok ? "true" : "false", ok);
  cout << (ok ? "PASS longest_word\n" : "FAIL longest_word\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}

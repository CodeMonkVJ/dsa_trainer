#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  bool ok = wordBreak("leetcode", {"leet", "code"}) &&
            !wordBreak("catsandog", {"cats", "dog", "sand", "and", "cat"});
  dsa_test::emit_case("{\"problem\":\"word_break\"}", "true",
                      ok ? "true" : "false", ok);
  cout << (ok ? "PASS word_break\n" : "FAIL word_break\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}

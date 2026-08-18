#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  bool first = wordBreak("leetcode", {"leet", "code"});
  bool second = wordBreak("catsandog", {"cats", "dog", "sand", "and", "cat"});
  bool ok = first && !second;
  dsa_test::emit_case(
      "{\"first_text\":\"leetcode\",\"first_dictionary\":[\"leet\",\"code\"],"
      "\"second_text\":\"catsandog\",\"second_dictionary\":[\"cats\",\"dog\","
      "\"sand\",\"and\",\"cat\"]}",
      "{\"first\":true,\"second\":false}",
      "{\"first\":" + string(first ? "true" : "false") +
          ",\"second\":" + string(second ? "true" : "false") + "}",
      ok);
  cout << (ok ? "PASS word break\n" : "FAIL word break\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}

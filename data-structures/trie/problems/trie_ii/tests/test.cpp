#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  bool ok = true;
  dsa_test::emit_case("{\"problem\":\"trie_ii\"}", "true",
                      ok ? "true" : "false", ok);
  TrieII t;
  t.insert("apple");
  t.insert("apple");
  t.insert("app");
  ok =
      t.countWordsEqualTo("apple") == 2 && t.countWordsStartingWith("app") == 3;
  t.erase("apple");
  ok = ok && t.countWordsEqualTo("apple") == 1;
  cout << (ok ? "PASS trie_ii\n" : "FAIL trie_ii\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}

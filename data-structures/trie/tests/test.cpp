#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }
int main() {
  Trie trie; check(trie.insert("cat") && trie.insert("car"), "insert words");
  check(trie.contains("cat") && !trie.contains("ca") && !trie.contains("dog"), "exact lookup");
  check(trie.startsWith("ca") && trie.startsWith("") && !trie.startsWith("do"), "prefix lookup");
  check(!trie.insert("Cat") && !trie.contains("Cat"), "reject uppercase input");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}

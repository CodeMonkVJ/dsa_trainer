#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  int actual = minPalindromeCuts("aab");
  bool ok = actual == 1;
  dsa_test::emit_case("{\"text\":\"aab\"}", "1", to_string(actual), ok);
  cout << (ok ? "PASS palindrome_partition\n" : "FAIL palindrome_partition\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}

#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(string input, int expected, int actual) {
  bool ok = expected == actual;
  ++total;
  passed += ok;
  dsa_test::emit_case(input, to_string(expected), to_string(actual), ok);
}
int main() {
  check(R"({"value":""})", 0, minCharsForPalindrome(""));
  check(R"({"value":"a"})", 0, minCharsForPalindrome("a"));
  check(R"({"value":"aba"})", 0, minCharsForPalindrome("aba"));
  check(R"({"value":"abcd"})", 3, minCharsForPalindrome("abcd"));
  check(R"({"value":"aacecaaa"})", 1, minCharsForPalindrome("aacecaaa"));
  check(R"({"value":"AACECAAAA"})", 2, minCharsForPalindrome("AACECAAAA"));
  check(R"({"value":"aaab"})", 1, minCharsForPalindrome("aaab"));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

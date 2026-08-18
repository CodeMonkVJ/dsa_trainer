#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
string q(const string &s) {
  string r = "\"";
  for (char c : s) {
    if (c == '\"' || c == '\\')
      r += '\\';
    r += c;
  }
  return r + '"';
}
bool pal(const string &s) {
  return equal(s.begin(), s.begin() + s.size() / 2, s.rbegin());
}
void check(string input, string expected, string actual) {
  bool ok = expected == actual;
  ++total;
  passed += ok;
  dsa_test::emit_case(input, q(expected), q(actual), ok);
}
int main() {
  check(R"({"value":"babad"})", "bab", longestPalindromicSubstring("babad"));
  check(R"({"value":"cbbd"})", "bb", longestPalindromicSubstring("cbbd"));
  check(R"({"value":"a"})", "a", longestPalindromicSubstring("a"));
  check(R"({"value":""})", "", longestPalindromicSubstring(""));
  string result = longestPalindromicSubstring("forgeeksskeegfor");
  bool long_ok = result == "geeksskeeg" && pal(result);
  ++total;
  passed += long_ok;
  dsa_test::emit_case(R"({"value":"forgeeksskeegfor"})", "\"geeksskeeg\"",
                      q(result), long_ok);
  check(R"({"value":"aaaa"})", "aaaa", longestPalindromicSubstring("aaaa"));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

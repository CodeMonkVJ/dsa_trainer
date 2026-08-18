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
    if (c == '\n')
      r += "\\n";
    else if (c == '\t')
      r += "\\t";
    else
      r += c;
  }
  return r + '"';
}
void check(string input, string expected, string actual) {
  bool ok = expected == actual;
  ++total;
  passed += ok;
  dsa_test::emit_case(input, q(expected), q(actual), ok);
}
int main() {
  check(R"({"value":"  the sky is blue  "})", "blue is sky the",
        reverseWords("  the sky is blue  "));
  check(R"({"value":"hello"})", "hello", reverseWords("hello"));
  check(R"({"value":"one   two\\tthree\\n"})", "three two one",
        reverseWords("one   two\tthree\n"));
  check(R"({"value":"   \\t  "})", "", reverseWords("   \t  "));
  check(R"({"value":"a b a"})", "a b a", reverseWords("a b a"));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

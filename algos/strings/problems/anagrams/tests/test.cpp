#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
string j(string_view value) {
  string out = "\"";
  for (char c : value) {
    if (c == '\\')
      out += "\\\\";
    else if (c == '\"')
      out += "\\\"";
    else if (c == '\n')
      out += "\\n";
    else if (c == '\t')
      out += "\\t";
    else if (c == '\r')
      out += "\\r";
    else
      out += c;
  }
  return out + '"';
}
void check(string input, bool expected, bool actual) {
  ++total;
  bool ok = expected == actual;
  passed += ok;
  dsa_test::emit_case(input, expected ? "true" : "false",
                      actual ? "true" : "false", ok);
}

int main() {
  check(R"({"first":"listen","second":"silent"})", true,
        areAnagrams("listen", "silent"));
  check(R"({"first":"","second":""})", true, areAnagrams("", ""));
  check(R"({"first":"aabbcc","second":"abcabc"})", true,
        areAnagrams("aabbcc", "abcabc"));
  check(R"({"first":"rat","second":"car"})", false, areAnagrams("rat", "car"));
  check(R"({"first":"abc","second":"ab"})", false, areAnagrams("abc", "ab"));
  check(R"({"first":"Dormitory","second":"Dirtyroom"})", true,
        areAnagrams("Dormitory", "Dirtyroom"));
  check(R"({"first":"a b!","second":"! ba"})", true,
        areAnagrams("a b!", "! ba"));
  string bytes(256, '\0');
  check(R"({"first":"256 NUL bytes","second":"256 NUL bytes"})", true,
        areAnagrams(bytes, bytes));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

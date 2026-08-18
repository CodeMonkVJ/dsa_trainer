#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
string q(const string &s) { return "\"" + s + "\""; }
void check(string input, string expected, string actual) {
  bool ok = expected == actual;
  ++total;
  passed += ok;
  dsa_test::emit_case(input, q(expected), q(actual), ok);
}
void check(string input, int expected, int actual) {
  bool ok = expected == actual;
  ++total;
  passed += ok;
  dsa_test::emit_case(input, to_string(expected), to_string(actual), ok);
}
int main() {
  check(R"({"roman":"III"})", 3, romanToInteger("III"));
  check(R"({"roman":"LVIII"})", 58, romanToInteger("LVIII"));
  check(R"({"roman":"MCMXCIV"})", 1994, romanToInteger("MCMXCIV"));
  check(R"({"roman":"IV"})", 4, romanToInteger("IV"));
  check(R"({"roman":"MMMCMXCIX"})", 3999, romanToInteger("MMMCMXCIX"));
  check(R"({"roman":""})", 0, romanToInteger(""));
  check(R"({"number":1994})", "MCMXCIV", integerToRoman(1994));
  check(R"({"number":3999})", "MMMCMXCIX", integerToRoman(3999));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

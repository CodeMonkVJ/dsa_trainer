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
void check(string input, string expected, string actual) {
  bool ok = expected == actual;
  ++total;
  passed += ok;
  dsa_test::emit_case(input, q(expected), q(actual), ok);
}
int main() {
  check(R"({"words":["flower","flow","flight"]})", "fl",
        longestCommonPrefix({"flower", "flow", "flight"}));
  check(R"({"words":["dog","racecar","car"]})", "",
        longestCommonPrefix({"dog", "racecar", "car"}));
  check(R"({"words":["interspecies","interstellar","interstate"]})", "inters",
        longestCommonPrefix({"interspecies", "interstellar", "interstate"}));
  check(R"({"words":["alone"]})", "alone", longestCommonPrefix({"alone"}));
  check(R"({"words":[]})", "", longestCommonPrefix({}));
  check(R"({"words":["same","same","same"]})", "same",
        longestCommonPrefix({"same", "same", "same"}));
  check(R"({"words":["Case","case"]})", "",
        longestCommonPrefix({"Case", "case"}));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

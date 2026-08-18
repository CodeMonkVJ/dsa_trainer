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
void check(int n, string expected, string actual) {
  bool ok = expected == actual;
  ++total;
  passed += ok;
  dsa_test::emit_case("{\"n\":" + to_string(n) + "}", q(expected), q(actual),
                      ok);
}
int main() {
  check(-1, "", countAndSay(-1));
  check(1, "1", countAndSay(1));
  check(2, "11", countAndSay(2));
  check(5, "111221", countAndSay(5));
  check(6, "312211", countAndSay(6));
  check(8, "1113213211", countAndSay(8));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

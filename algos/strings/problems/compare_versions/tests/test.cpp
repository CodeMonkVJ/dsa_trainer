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
  check(R"({"left":"1.01","right":"1.001"})", 0,
        compareVersion("1.01", "1.001"));
  check(R"({"left":"1.0","right":"1.0.0"})", 0, compareVersion("1.0", "1.0.0"));
  check(R"({"left":"0.1","right":"1.1"})", -1, compareVersion("0.1", "1.1"));
  check(R"({"left":"1.0.1","right":"1"})", 1, compareVersion("1.0.1", "1"));
  check(R"({"left":"1.2","right":"1.10"})", -1, compareVersion("1.2", "1.10"));
  check(R"({"left":"1.0.0.0","right":"1"})", 0, compareVersion("1.0.0.0", "1"));
  check(R"({"left":"999999999999999999999","right":"1000000000000000000000"})",
        -1, compareVersion("999999999999999999999", "1000000000000000000000"));
  check(R"({"left":"2.1.3","right":"2.1.3"})", 0,
        compareVersion("2.1.3", "2.1.3"));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

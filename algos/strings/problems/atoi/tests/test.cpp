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
  check(R"({"value":"42"})", 42, parseAtoi("42"));
  check(R"({"value":"   -42"})", -42, parseAtoi("   -42"));
  check(R"({"value":"+17 with suffix"})", 17, parseAtoi("+17 with suffix"));
  check(R"({"value":"words and 987"})", 0, parseAtoi("words and 987"));
  check(R"({"value":"-91283472332"})", INT_MIN, parseAtoi("-91283472332"));
  check(R"({"value":"91283472332"})", INT_MAX, parseAtoi("91283472332"));
  check(R"({"value":"+-12"})", 0, parseAtoi("+-12"));
  check(R"({"value":""})", 0, parseAtoi(""));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

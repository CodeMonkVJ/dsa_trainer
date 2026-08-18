#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
template <typename T> string vec(const vector<T> &v) {
  string s = "[";
  for (size_t i = 0; i < v.size(); ++i) {
    if (i)
      s += ",";
    s += to_string(v[i]);
  }
  return s + "]";
}
void check(string input, string expected, string actual) {
  bool ok = expected == actual;
  ++total;
  passed += ok;
  dsa_test::emit_case(input, expected, actual, ok);
}
int main() {
  check(R"({"value":""})", "[]", vec(zFunction("")));
  check(R"({"value":"a"})", "[0]", vec(zFunction("a")));
  check(R"({"value":"aaaaa"})", "[0,4,3,2,1]", vec(zFunction("aaaaa")));
  check(R"({"value":"aabcaab"})", "[0,1,0,0,3,1,0]", vec(zFunction("aabcaab")));
  check(R"({"value":"abacaba"})", "[0,0,1,0,3,0,1]", vec(zFunction("abacaba")));
  check(R"({"value":"1110111"})", "[0,2,1,0,3,2,1]", vec(zFunction("1110111")));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

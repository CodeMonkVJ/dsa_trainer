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
  check(R"({"text":"ababcabcabababd","pattern":"ababd"})", "[10]",
        vec(rabinKarpSearch("ababcabcabababd", "ababd")));
  check(R"({"text":"aaaaa","pattern":"aaa"})", "[0,1,2]",
        vec(rabinKarpSearch("aaaaa", "aaa")));
  check(R"({"text":"hello world","pattern":"world"})", "[6]",
        vec(rabinKarpSearch("hello world", "world")));
  check(R"({"text":"abcdef","pattern":"xyz"})", "[]",
        vec(rabinKarpSearch("abcdef", "xyz")));
  check(R"({"text":"short","pattern":"long pattern"})", "[]",
        vec(rabinKarpSearch("short", "long pattern")));
  check(R"({"text":"abc","pattern":""})", "[]",
        vec(rabinKarpSearch("abc", "")));
  check(R"({"text":"AaAa","pattern":"Aa"})", "[0,2]",
        vec(rabinKarpSearch("AaAa", "Aa")));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

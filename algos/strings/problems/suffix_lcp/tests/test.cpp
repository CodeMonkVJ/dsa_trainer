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
  SuffixArray banana("banana");
  check(R"({"value":"banana","field":"suffix_array"})", "[5,3,1,0,4,2]",
        vec(banana.sa));
  check(R"({"value":"banana","field":"lcp"})", "[1,3,0,0,2]", vec(banana.lcp));
  SuffixArray empty("");
  check(R"({"value":"","field":"suffix_array_and_lcp"})",
        "{\"sa\":[],\"lcp\":[]}",
        "{\"sa\":" + vec(empty.sa) + ",\"lcp\":" + vec(empty.lcp) + "}");
  SuffixArray repeated("aaaa");
  string repeated_actual =
      "{\"sa\":" + vec(repeated.sa) + ",\"lcp\":" + vec(repeated.lcp) + "}";
  check(R"({"value":"aaaa","field":"suffix_array_and_lcp"})",
        "{\"sa\":[3,2,1,0],\"lcp\":[1,2,3]}", repeated_actual);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

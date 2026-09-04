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
      vec(findOccurrences("ababcabcabababd", "ababd")));

  check(R"({"text":"aaaaa","pattern":"aaa"})", "[0,1,2]",
        vec(findOccurrences("aaaaa", "aaa")));
  
  check(R"({"text":"abcdef","pattern":"xyz"})", "[]",
        vec(findOccurrences("abcdef", "xyz")));
  
  check(R"({"text":"abc","pattern":""})", "[]",
        vec(findOccurrences("abc", "")));
  
  check(R"({"text":"abc","pattern":"abc"})", "[0]",
        vec(findOccurrences("abc", "abc")));
  
  check(R"({"text":"abc","pattern":"abcd"})", "[]",
        vec(findOccurrences("abc", "abcd")));
  
  check(R"({"text":"abcabc","pattern":"abc"})", "[0,3]",
        vec(findOccurrences("abcabc", "abc")));
  
  check(R"({"text":"ababa","pattern":"aba"})", "[0,2]",
        vec(findOccurrences("ababa", "aba")));
  
  check(R"({"text":"aaaa","pattern":"aa"})", "[0,1,2]",
        vec(findOccurrences("aaaa", "aa")));
  
  check(R"({"text":"bbbb","pattern":"b"})", "[0,1,2,3]",
        vec(findOccurrences("bbbb", "b")));
  
  check(R"({"text":"abcabcabc","pattern":"cab"})", "[2,5]",
        vec(findOccurrences("abcabcabc", "cab")));
  
  check(R"({"text":"ababababac","pattern":"ababac"})", "[4]",
        vec(findOccurrences("ababababac", "ababac")));
  
  check(R"({"text":"aaabaaaab","pattern":"aaaab"})", "[4]",
        vec(findOccurrences("aaabaaaab", "aaaab")));
  
  check(R"({"text":"","pattern":"a"})", "[]",
        vec(findOccurrences("", "a")));
  
  check(R"({"text":"","pattern":""})", "[]",
        vec(findOccurrences("", "")));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

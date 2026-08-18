#include <bits/stdc++.h>
using namespace std;
#include "../../../../../test_protocol.hpp"

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;
void check(bool condition, const char *input, bool expected) {
  ++total;
  if (condition)
    ++passed;
  dsa_test::emit_case(input, expected ? "true" : "false",
                      condition ? "true" : "false", condition == expected);
}

int main() {
  check(wordBreak("leetcode", {"leet", "code"}),
        R"({"text":"leetcode","dictionary":["leet","code"]})", true);
  check(wordBreak("applepenapple", {"apple", "pen"}),
        R"({"text":"applepenapple","dictionary":["apple","pen"]})", true);
  check(
      !wordBreak("catsandog", {"cats", "dog", "sand", "and", "cat"}),
      R"({"text":"catsandog","dictionary":["cats","dog","sand","and","cat"]})",
      true);
  check(wordBreak("", {"a"}), R"({"text":"","dictionary":["a"]})", true);
  check(!wordBreak("abc", {}), R"({"text":"abc","dictionary":[]})", true);
  check(wordBreak("cars", {"car", "ca", "rs"}),
        R"({"text":"cars","dictionary":["car","ca","rs"]})", true);
  check(!wordBreak("A", {"a"}), R"({"text":"A","dictionary":["a"]})", true);
  check(wordBreak("aaaaaaa", {"", "aaaa", "aaa"}),
        R"({"text":"aaaaaaa","dictionary":["","aaaa","aaa"]})", true);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

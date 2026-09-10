#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(string input, int expected, int actual) {
  bool ok = expected == actual;
  ++total;

  if (ok)
    ++passed;

  dsa_test::emit_case(
      input,
      to_string(expected),
      to_string(actual),
      ok);
}

int main() {
  check(R"({"value":""})",
        0,
        minCharsForPalindrome(""));

  check(R"({"value":"a"})",
        0,
        minCharsForPalindrome("a"));

  check(R"({"value":"aa"})",
        0,
        minCharsForPalindrome("aa"));

  check(R"({"value":"aba"})",
        0,
        minCharsForPalindrome("aba"));

  check(R"({"value":"abba"})",
        0,
        minCharsForPalindrome("abba"));

  check(R"({"value":"racecar"})",
        0,
        minCharsForPalindrome("racecar"));

  check(R"({"value":"ab"})",
        1,
        minCharsForPalindrome("ab"));

  check(R"({"value":"abc"})",
        2,
        minCharsForPalindrome("abc"));

  check(R"({"value":"abcd"})",
        3,
        minCharsForPalindrome("abcd"));

  check(R"({"value":"aacecaaa"})",
        1,
        minCharsForPalindrome("aacecaaa"));

  check(R"({"value":"aaab"})",
        1,
        minCharsForPalindrome("aaab"));

  check(R"({"value":"abcdabc"})",
        6,
        minCharsForPalindrome("abcdabc"));

  check(R"({"value":"aaaa"})",
        0,
        minCharsForPalindrome("aaaa"));

  check(R"({"value":"aaaab"})",
        1,
        minCharsForPalindrome("aaaab"));

  check(R"({"value":"baaaa"})",
        4,
        minCharsForPalindrome("baaaa"));

  check(R"({"value":"aab"})",
        1,
        minCharsForPalindrome("aab"));

  check(R"({"value":"aaba"})",
        2,
        minCharsForPalindrome("aaba"));

  check(R"({"value":"aabb"})",
        2,
        minCharsForPalindrome("aabb"));

  check(R"({"value":"abbacd"})",
        2,
        minCharsForPalindrome("abbacd"));

  check(R"({"value":"Aa"})",
        1,
        minCharsForPalindrome("Aa"));

  check(R"({"value":"aA"})",
        1,
        minCharsForPalindrome("aA"));

  check(R"({"value":"AaA"})",
        0,
        minCharsForPalindrome("AaA"));

  check(R"({"value":"a a"})",
        0,
        minCharsForPalindrome("a a"));

  check(R"({"value":"ab!"})",
        2,
        minCharsForPalindrome("ab!"));

  check(R"({"value":"!ab"})",
        2,
        minCharsForPalindrome("!ab"));

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
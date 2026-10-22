#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

void check(const string &text, int expected, const char *name) {
  ++total;

  int actual = minPalindromeCuts(text);
  bool ok = actual == expected;

  if (ok)
    ++passed;

  string input = "{\"case\":\"" + string(name) +
                 "\",\"text\":\"" + text + "\"}";

  dsa_test::emit_case(
      input,
      to_string(expected),
      to_string(actual),
      ok);

  cout << (ok ? "PASS " : "FAIL ")
       << name << '\n';
}

int main() {
  check(
      "",
      0,
      "empty string");

  check(
      "a",
      0,
      "single character");

  check(
      "aa",
      0,
      "two equal characters");

  check(
      "ab",
      1,
      "two different characters");

  check(
      "aab",
      1,
      "classic example");

  check(
      "abba",
      0,
      "whole string even palindrome");

  check(
      "racecar",
      0,
      "whole string odd palindrome");

  check(
      "aaaaaa",
      0,
      "all same characters");

  check(
      "abc",
      2,
      "all distinct characters");

  check(
      "abcdef",
      5,
      "all distinct longer string");

  check(
      "aba",
      0,
      "simple odd palindrome");

  check(
      "aabaa",
      0,
      "nested palindrome");

  check(
      "abac",
      1,
      "palindrome prefix");

  // "a | bcb"
  check(
      "abcb",
      1,
      "palindrome suffix");

  // "aa | b"
  check(
      "aab",
      1,
      "palindrome prefix plus final char");

  // "a | bb | a" is not optimal because whole string is palindrome.
  check(
      "abba",
      0,
      "avoid unnecessary internal cuts");

  // "a | bccb | c"
  check(
      "abccbc",
      2,
      "internal long palindrome");

  // "noon | abba"
  check(
      "noonabba",
      1,
      "two large palindromic pieces");

  // "aba | cdc"
  check(
      "abacdc",
      1,
      "two odd palindromes");

  // "a | babbbab"
  check(
      "ababbbabbababa",
      3,
      "classic harder partition");

  check(
      "banana",
      1,
      "long palindrome suffix");

  check(
      "cdd",
      1,
      "even palindrome suffix");

  check(
      "abcbaefgfe",
      1,
      "multiple palindrome regions");

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
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

void check(const string &input,
           const string &expected,
           const char *name) {
  string actual = longestPalindromicSubstring(input);
  bool ok = (actual == expected);

  ++total;
  if (ok)
    ++passed;

  cout << (ok ? "PASS " : "FAIL ")
       << name
       << " expected=" << q(expected)
       << " actual=" << q(actual)
       << '\n';

  string jsonInput =
      string("{\"value\":") + q(input) + "}";

  dsa_test::emit_case(
      jsonInput,
      q(expected),
      q(actual),
      ok);
}

int main() {
  // Empty / singleton.
  check("", "", "empty string");
  check("a", "a", "single character");

  // Standard odd palindrome.
  check(
      "babad",
      "bab",
      "odd palindrome with earliest tie");

  // Standard even palindrome.
  check(
      "cbbd",
      "bb",
      "even palindrome");

  // Entire string is palindrome.
  check(
      "racecar",
      "racecar",
      "whole odd length palindrome");

  check(
      "abba",
      "abba",
      "whole even length palindrome");

  // No palindrome longer than one character.
  // Earliest one should win.
  check(
      "abcd",
      "a",
      "no multi character palindrome");

  // Repeated characters.
  check(
      "aaaa",
      "aaaa",
      "all same characters");

  check(
      "aaaaa",
      "aaaaa",
      "all same odd length");

  // Palindrome at beginning.
  check(
      "abacxyz",
      "aba",
      "palindrome at beginning");

  // Palindrome at end.
  check(
      "xyzracecar",
      "racecar",
      "palindrome at end");

  // Long palindrome in middle.
  check(
      "forgeeksskeegfor",
      "geeksskeeg",
      "long middle palindrome");

  // Equal-length palindromes:
  // "aba" starts before "cdc".
  check(
      "abacdc",
      "aba",
      "earliest palindrome wins tie");

  // Another tie case.
  // "aa" appears before "bb".
  check(
      "aabb",
      "aa",
      "earliest even palindrome wins tie");

  // Nested palindrome choices.
  check(
      "bananas",
      "anana",
      "nested odd palindromes");

  // Even palindrome surrounded by other characters.
  check(
      "xabbay",
      "abba",
      "embedded even palindrome");

  // Multiple candidate centers.
  check(
      "abaxyzzyxf",
      "xyzzyx",
      "multiple centers");

  // Small edge cases.
  check(
      "aa",
      "aa",
      "two equal characters");

  check(
      "ab",
      "a",
      "two different characters");

  check(
      "aba",
      "aba",
      "three character palindrome");

  check(
      "aab",
      "aa",
      "even palindrome at start");

  check(
      "baa",
      "aa",
      "even palindrome at end");

  // Mixed case is case-sensitive.
  check(
      "AaA",
      "AaA",
      "case sensitive valid palindrome");

  check(
      "Aa",
      "A",
      "case sensitive mismatch");

  // Spaces are ordinary characters.
  check(
      "a a",
      "a a",
      "spaces inside palindrome");

  // Punctuation is ordinary too.
  check(
      "a!a",
      "a!a",
      "punctuation inside palindrome");

  // Longer tricky case.
  check(
      "abcddcbaxyz",
      "abcddcba",
      "long palindrome prefix");

  // Palindrome appears after non-palindromic prefix.
  check(
      "xyzabcddcba",
      "abcddcba",
      "long palindrome suffix");

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
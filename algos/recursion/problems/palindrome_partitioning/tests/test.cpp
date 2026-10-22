#include <bits/stdc++.h>
using namespace std;

#include "../../../../../test_protocol.hpp"

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

set<vector<string>> normalize(const vector<vector<string>> &v) {
  return {v.begin(), v.end()};
}

void check(const string &input,
           const vector<vector<string>> &expected,
           const char *name) {
  ++total;

  auto actual = partition(input);

  auto actualSet = normalize(actual);
  auto expectedSet = normalize(expected);

  bool ok =
      actualSet == expectedSet &&
      actual.size() == actualSet.size();

  if (ok)
    ++passed;

  cout << (ok ? "PASS " : "FAIL ")
       << name
       << '\n';

  dsa_test::emit_case(
      string("{\"text\":\"") + input + "\"}",
      "expected partitions",
      ok ? "true" : "false",
      ok);
}

int main() {
  // Empty string.
  check(
      "",
      {{}},
      "empty string");

  // Single character.
  check(
      "a",
      {
          {"a"}
      },
      "single character");

  // No palindrome longer than 1.
  check(
      "abc",
      {
          {"a", "b", "c"}
      },
      "no multi character palindrome");

  // Standard example.
  check(
      "aab",
      {
          {"a", "a", "b"},
          {"aa", "b"}
      },
      "standard aab");

  // Whole string palindrome.
  check(
      "aba",
      {
          {"a", "b", "a"},
          {"aba"}
      },
      "whole odd palindrome");

  // Whole even palindrome.
  check(
      "abba",
      {
          {"a", "b", "b", "a"},
          {"a", "bb", "a"},
          {"abba"}
      },
      "whole even palindrome");

  // Repeated characters.
  check(
      "aaa",
      {
          {"a", "a", "a"},
          {"a", "aa"},
          {"aa", "a"},
          {"aaa"}
      },
      "all repeated characters");

  // Larger repeated case.
  check(
      "aaaa",
      {
          {"a", "a", "a", "a"},
          {"a", "a", "aa"},
          {"a", "aa", "a"},
          {"a", "aaa"},
          {"aa", "a", "a"},
          {"aa", "aa"},
          {"aaa", "a"},
          {"aaaa"}
      },
      "four repeated characters");

  // Palindrome only at the beginning.
  check(
      "aabc",
      {
          {"a", "a", "b", "c"},
          {"aa", "b", "c"}
      },
      "palindrome prefix");

  // Palindrome only at the end.
  check(
      "abcc",
      {
          {"a", "b", "c", "c"},
          {"a", "b", "cc"}
      },
      "palindrome suffix");

  // Multiple different palindrome choices.
  check(
      "aabaa",
      {
          {"a", "a", "b", "a", "a"},
          {"a", "a", "b", "aa"},
          {"a", "aba", "a"},
          {"aa", "b", "a", "a"},
          {"aa", "b", "aa"},
          {"aabaa"}
      },
      "nested palindrome choices");

  // Mixed odd and even palindromes.
  check(
      "abbaeae",
      {
          {"a", "b", "b", "a", "e", "a", "e"},
          {"a", "b", "b", "a", "eae"},
          {"a", "bb", "a", "e", "a", "e"},
          {"a", "bb", "a", "eae"},
          {"abba", "e", "a", "e"},
          {"abba", "eae"},
          {"a", "b", "b", "aea", "e"},
          {"a", "bb", "aea", "e"}
      },
      "mixed odd and even palindromes");

  // Case-sensitive.
  check(
      "AaA",
      {
          {"A", "a", "A"},
          {"AaA"}
      },
      "case sensitive palindrome");

  // Similar-looking but not palindrome due to case.
  check(
      "Aa",
      {
          {"A", "a"}
      },
      "case mismatch");

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
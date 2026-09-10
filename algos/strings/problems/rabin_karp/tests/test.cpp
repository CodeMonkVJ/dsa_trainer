#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

template <typename T>
string vec(const vector<T> &v) {
  string s = "[";
  for (size_t i = 0; i < v.size(); ++i) {
    if (i)
      s += ",";
    s += to_string(v[i]);
  }
  return s + "]";
}

void check(string input, string expected, string actual, const char *name) {
  bool ok = expected == actual;

  ++total;
  if (ok)
    ++passed;

  dsa_test::emit_case(input, expected, actual, ok);
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  // Standard KMP/Rabin-Karp-style example.
  check(R"({"text":"ababcabcabababd","pattern":"ababd"})",
        "[10]",
        vec(rabinKarpSearch("ababcabcabababd", "ababd")),
        "standard match");

  // Overlapping matches.
  check(R"({"text":"aaaaa","pattern":"aaa"})",
        "[0,1,2]",
        vec(rabinKarpSearch("aaaaa", "aaa")),
        "overlapping matches");

  // Match at the beginning.
  check(R"({"text":"abcdef","pattern":"abc"})",
        "[0]",
        vec(rabinKarpSearch("abcdef", "abc")),
        "match at beginning");

  // Match at the very end.
  check(R"({"text":"abcdef","pattern":"def"})",
        "[3]",
        vec(rabinKarpSearch("abcdef", "def")),
        "match at end");

  // Pattern equals entire text.
  check(R"({"text":"abc","pattern":"abc"})",
        "[0]",
        vec(rabinKarpSearch("abc", "abc")),
        "pattern equals text");

  // Pattern longer than text.
  check(R"({"text":"short","pattern":"long pattern"})",
        "[]",
        vec(rabinKarpSearch("short", "long pattern")),
        "pattern longer than text");

  // Empty pattern.
  check(R"({"text":"abc","pattern":""})",
        "[]",
        vec(rabinKarpSearch("abc", "")),
        "empty pattern");

  // Pattern absent.
  check(R"({"text":"abcdef","pattern":"xyz"})",
        "[]",
        vec(rabinKarpSearch("abcdef", "xyz")),
        "pattern absent");

  // Single-character pattern with multiple matches.
  check(R"({"text":"banana","pattern":"a"})",
        "[1,3,5]",
        vec(rabinKarpSearch("banana", "a")),
        "single character pattern");

  // Single-character repeated text.
  check(R"({"text":"bbbbbb","pattern":"bb"})",
        "[0,1,2,3,4]",
        vec(rabinKarpSearch("bbbbbb", "bb")),
        "many overlapping short matches");

  // Case sensitivity.
  check(R"({"text":"AaAaAa","pattern":"Aa"})",
        "[0,2,4]",
        vec(rabinKarpSearch("AaAaAa", "Aa")),
        "case sensitive matching");

  // Spaces and punctuation are normal characters.
  check(R"({"text":"a+b+a+b","pattern":"b+a"})",
        "[2]",
        vec(rabinKarpSearch("a+b+a+b", "b+a")),
        "punctuation and symbols");

  // Repeated prefix/suffix structure.
  check(R"({"text":"abababab","pattern":"abab"})",
        "[0,2,4]",
        vec(rabinKarpSearch("abababab", "abab")),
        "repeated prefix structure");

  // False candidates must be rejected by character verification.
  check(R"({"text":"abcabc","pattern":"abd"})",
        "[]",
        vec(rabinKarpSearch("abcabc", "abd")),
        "hash candidate verification");

  // Match after several non-matching windows.
  check(R"({"text":"zzzzabczzzz","pattern":"abc"})",
        "[4]",
        vec(rabinKarpSearch("zzzzabczzzz", "abc")),
        "match after several windows");

  // Text itself empty.
  check(R"({"text":"","pattern":"a"})",
        "[]",
        vec(rabinKarpSearch("", "a")),
        "empty text");

  // Both empty.
  check(R"({"text":"","pattern":""})",
        "[]",
        vec(rabinKarpSearch("", "")),
        "both empty");

  // Embedded null byte: std::string is byte-oriented.
  check(R"({"text":"a\0bc\0a","pattern":"\0a"})",
      "[4]",
      vec(rabinKarpSearch(string("a\0bc\0a", 6),
                          string("\0a", 2))),
      "embedded null bytes");

  // High-byte values: catches signed-char indexing/conversion mistakes.
  check(
      R"({"text":"\x80\x81\x80\x82","pattern":"\x80\x81"})",
      "[0]",
      vec(rabinKarpSearch(
          string("\x80\x81\x80\x82", 4),
          string("\x80\x81", 2))),
      "high byte values");

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
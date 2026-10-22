#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

void check(const string &first,
           const string &second,
           int expected,
           const char *name) {
  int actual = editDistance(first, second);
  bool ok = actual == expected;

  ++total;
  if (ok)
    ++passed;

  string input =
      "{\"first\":\"" + first +
      "\",\"second\":\"" + second + "\"}";

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
      "",
      0,
      "both empty");

  check(
      "",
      "abc",
      3,
      "insert into empty");

  check(
      "abc",
      "",
      3,
      "delete to empty");

  check(
      "abc",
      "abc",
      0,
      "identical strings");

  check(
      "a",
      "b",
      1,
      "single replacement");

  check(
      "a",
      "ab",
      1,
      "single insertion");

  check(
      "ab",
      "a",
      1,
      "single deletion");

  check(
      "horse",
      "ros",
      3,
      "classic horse to ros");

  check(
      "kitten",
      "sitting",
      3,
      "classic kitten to sitting");

  check(
      "cat",
      "cut",
      1,
      "replacement in middle");

  check(
      "abc",
      "yabc",
      1,
      "insert at front");

  check(
      "abc",
      "abcy",
      1,
      "insert at end");

  check(
      "yabc",
      "abc",
      1,
      "delete at front");

  check(
      "abcy",
      "abc",
      1,
      "delete at end");

  check(
      "abc",
      "xyz",
      3,
      "all characters replaced");

  check(
      "aaaa",
      "aa",
      2,
      "repeated characters deletion");

  check(
      "aa",
      "aaaa",
      2,
      "repeated characters insertion");

  check(
      "abab",
      "baba",
      2,
      "shifted repeating pattern");

  check(
      "Saturday",
      "Sunday",
      3,
      "mixed insert delete replace");

  check(
      "intention",
      "execution",
      5,
      "long classic example");

  check(
      "ABC",
      "abc",
      3,
      "case sensitive");

  check(
      "aab",
      "aba",
      2,
      "duplicate characters");

  check(
      "abcdef",
      "azced",
      3,
      "mixed operations");

  // Distance should be symmetric.
  {
    int a = editDistance("flaw", "lawn");
    int b = editDistance("lawn", "flaw");

    bool ok = a == 2 && b == 2 && a == b;

    ++total;
    if (ok)
      ++passed;

    dsa_test::emit_case(
        "{\"first\":\"flaw\",\"second\":\"lawn\"}",
        "2",
        to_string(a),
        ok);

    cout << (ok ? "PASS " : "FAIL ")
         << "distance symmetry\n";
  }

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
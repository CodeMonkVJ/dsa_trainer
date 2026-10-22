#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

string q(const string &s) {
  return "\"" + s + "\"";
}

void check(const string &input,
           const string &expected,
           const char *name) {
  string actual = reverseWords(input);
  bool ok = (actual == expected);

  ++total;
  if (ok)
    ++passed;

  cout << (ok ? "PASS " : "FAIL ")
       << name
       << " expected=" << q(expected)
       << " actual=" << q(actual)
       << '\n';

  dsa_test::emit_case(
      string("{\"value\":") + q(input) + "}",
      q(expected),
      q(actual),
      ok);
}

int main() {
  check(
      "",
      "",
      "empty string");

  check(
      "     ",
      "",
      "spaces only");

  check(
      "hello",
      "hello",
      "single word");

  check(
      "   hello   ",
      "hello",
      "single word with surrounding spaces");

  check(
      "  the sky is blue  ",
      "blue is sky the",
      "standard example");

  check(
      "one   two    three",
      "three two one",
      "multiple spaces between words");

  check(
      "hello world",
      "world hello",
      "two words");

  check(
      "a b c d e",
      "e d c b a",
      "single character words");

  check(
      "a b a",
      "a b a",
      "repeated words");

  check(
      "x x x x",
      "x x x x",
      "all words identical");

  check(
      "One TWO three",
      "three TWO One",
      "case preserved");

  check(
      "123 456 789",
      "789 456 123",
      "numeric words");

  check(
      "hello, world!",
      "world! hello,",
      "punctuation preserved");

  check(
      "a-b c_d xyz",
      "xyz c_d a-b",
      "symbols inside words");

  check(
      "this is a longer sentence for testing",
      "testing for sentence longer a is this",
      "longer sentence");

  check(
      "  hello,   brave   new world!  ",
      "world! new brave hello,",
      "punctuation with extra spaces");

  check(
      "red blue red",
      "red blue red",
      "symmetric word sequence");

  check(
      "    one      two   ",
      "two one",
      "large spacing");

  check(
      "first second third fourth",
      "fourth third second first",
      "four word sentence");

  check(
      "a  bb   ccc    dddd",
      "dddd ccc bb a",
      "different word lengths");

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}
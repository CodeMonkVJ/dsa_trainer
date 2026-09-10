#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

void check(bool ok, const char *name) {
  ++total;
  if (ok)
    ++passed;

  cout << (ok ? "PASS " : "FAIL ") << name << '\n';

  string input = string("{\"test\":\"") + name + "\"}";
  dsa_test::emit_case(
      input,
      ok ? "true" : "false",
      ok ? "true" : "false",
      ok);
}

int main() {
  // Empty / no brackets.
  check(isBalanced(""), "empty string");
  check(isBalanced("letters only"), "ignore non brackets");
  check(isBalanced("123 + abc - xyz"), "ignore arbitrary text");

  // Single bracket cases.
  check(!isBalanced("("), "single unmatched open round");
  check(!isBalanced("["), "single unmatched open square");
  check(!isBalanced("{"), "single unmatched open curly");

  check(!isBalanced(")"), "single unmatched close round");
  check(!isBalanced("]"), "single unmatched close square");
  check(!isBalanced("}"), "single unmatched close curly");

  // Simplest valid pairs.
  check(isBalanced("()"), "single round pair");
  check(isBalanced("[]"), "single square pair");
  check(isBalanced("{}"), "single curly pair");

  // Sequential pairs.
  check(isBalanced("()[]{}"), "sequential balanced pairs");
  check(isBalanced("{}()[]"), "sequential pairs different order");

  // Nested.
  check(isBalanced("([]{})"), "valid mixed nesting");
  check(isBalanced("{[()]}"), "deep mixed nesting");
  check(isBalanced("(((())))"), "deep same type nesting");

  // Valid expressions containing non-brackets.
  check(
      isBalanced("a + (b * [c - {d}])"),
      "balanced expression");

  check(
      isBalanced("func(a[2], {x: (y + z)})"),
      "balanced code-like text");

  // Wrong closing type.
  check(!isBalanced("(]"), "round closed by square");
  check(!isBalanced("[}"), "square closed by curly");
  check(!isBalanced("{)"), "curly closed by round");

  // Crossing / mismatched nesting.
  check(!isBalanced("([)]"), "crossed nesting");
  check(!isBalanced("{[}]"), "mismatched nested close");
  check(!isBalanced("((}"), "wrong closer after opens");

  // Closing bracket appears too early.
  check(!isBalanced(")("), "closing before opening");
  check(!isBalanced("]["),
        "square closing before opening");
  check(!isBalanced("}{"),
        "curly closing before opening");

  // Too many opens.
  check(!isBalanced("(())("), "extra opening round");
  check(!isBalanced("[[]"), "extra opening square");
  check(!isBalanced("{{}"), "extra opening curly");

  // Too many closes.
  check(!isBalanced("())"), "extra closing round");
  check(!isBalanced("[]]"), "extra closing square");
  check(!isBalanced("{}}"), "extra closing curly");

  // Correct prefix, invalid later.
  check(
      !isBalanced("()[]{}("),
      "valid prefix then unmatched open");

  check(
      !isBalanced("()[]{}]"),
      "valid prefix then unmatched close");

  // Long mixed valid case.
  check(
      isBalanced("a{b[c(d)e]f}g(h[i]{j})"),
      "long mixed valid nesting");

  // Long mixed invalid cases.
  check(
      !isBalanced("a{b[c(d)e}f]g"),
      "long mixed mismatched nesting");

  check(
      !isBalanced("abc(def[ghi{jkl}]"),
      "long mixed missing closer");

  // Lots of duplicate bracket types.
  check(
      isBalanced("[][][][]{{}}{{}}()()"),
      "many repeated balanced groups");

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
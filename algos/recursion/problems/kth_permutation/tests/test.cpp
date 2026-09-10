#include <bits/stdc++.h>
using namespace std;

#include "../../../../../test_protocol.hpp"

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int p = 0;
int t = 0;

void c(bool ok,
       const char *input,
       const char *expected,
       const string &actual) {
  ++t;

  if (ok)
    ++p;

  dsa_test::emit_case(
      input,
      expected,
      "\"" + actual + "\"",
      ok);

  cout << (ok ? "PASS " : "FAIL ") << input << '\n';
}

int main() {
  // n = 1
  {
    auto actual = getPermutation(1, 1);

    c(actual == "1",
      R"({"n":1,"k":1})",
      R"("1")",
      actual);
  }

  // First permutation.
  {
    auto actual = getPermutation(3, 1);

    c(actual == "123",
      R"({"n":3,"k":1})",
      R"("123")",
      actual);
  }

  // Middle permutation.
  {
    auto actual = getPermutation(3, 4);

    c(actual == "231",
      R"({"n":3,"k":4})",
      R"("231")",
      actual);
  }

  // Last permutation.
  {
    auto actual = getPermutation(3, 6);

    c(actual == "321",
      R"({"n":3,"k":6})",
      R"("321")",
      actual);
  }

  // k just outside valid range.
  {
    auto actual = getPermutation(3, 7);

    c(actual.empty(),
      R"({"n":3,"k":7})",
      R"("")",
      actual);
  }

  // k = 0 is invalid.
  {
    auto actual = getPermutation(3, 0);

    c(actual.empty(),
      R"({"n":3,"k":0})",
      R"("")",
      actual);
  }

  // n = 0 is invalid.
  {
    auto actual = getPermutation(0, 1);

    c(actual.empty(),
      R"({"n":0,"k":1})",
      R"("")",
      actual);
  }

  // n > 9 is invalid.
  {
    auto actual = getPermutation(10, 1);

    c(actual.empty(),
      R"({"n":10,"k":1})",
      R"("")",
      actual);
  }

  // n < 1 is invalid.
  {
    auto actual = getPermutation(-1, 1);

    c(actual.empty(),
      R"({"n":-1,"k":1})",
      R"("")",
      actual);
  }

  // n = 4, first permutation.
  {
    auto actual = getPermutation(4, 1);

    c(actual == "1234",
      R"({"n":4,"k":1})",
      R"("1234")",
      actual);
  }

  // n = 4, second block.
  {
    auto actual = getPermutation(4, 7);

    c(actual == "2134",
      R"({"n":4,"k":7})",
      R"("2134")",
      actual);
  }

  // n = 4, transition between blocks.
  {
    auto actual = getPermutation(4, 6);

    c(actual == "1432",
      R"({"n":4,"k":6})",
      R"("1432")",
      actual);
  }

  // n = 4, another middle position.
  {
    auto actual = getPermutation(4, 14);

    c(actual == "3142",
      R"({"n":4,"k":14})",
      R"("3142")",
      actual);
  }

  // n = 4, last permutation.
  {
    auto actual = getPermutation(4, 24);

    c(actual == "4321",
      R"({"n":4,"k":24})",
      R"("4321")",
      actual);
  }

  // k just outside n! for n = 4.
  {
    auto actual = getPermutation(4, 25);

    c(actual.empty(),
      R"({"n":4,"k":25})",
      R"("")",
      actual);
  }

  // n = 5, deeper block selection.
  {
    auto actual = getPermutation(5, 42);

    c(actual == "24531",
      R"({"n":5,"k":42})",
      R"("24531")",
      actual);
  }

  // n = 5, last permutation.
  {
    auto actual = getPermutation(5, 120);

    c(actual == "54321",
      R"({"n":5,"k":120})",
      R"("54321")",
      actual);
  }

  // n = 6, exercise several factorial levels.
  {
    auto actual = getPermutation(6, 400);

    c(actual == "425361",
      R"({"n":6,"k":400})",
      R"("425361")",
      actual);
  }

  cout << "DSA_RESULT {\"passed\":" << p
       << ",\"total\":" << t << "}\n";

  return p == t ? 0 : 1;
}
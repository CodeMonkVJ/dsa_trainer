#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(int eggs, int floors, int expected, const char *name) {
  ++total;

  int actual = minEggDrops(eggs, floors);
  bool ok = actual == expected;

  if (ok)
    ++passed;

  dsa_test::emit_case(
      "{\"eggs\":" + to_string(eggs) +
          ",\"floors\":" + to_string(floors) + "}",
      to_string(expected),
      to_string(actual),
      ok);

  cout << (ok ? "PASS " : "FAIL ") << name;

  if (!ok) {
    cout << ": expected " << expected
         << ", got " << actual;
  }

  cout << '\n';
}

int main() {
  // Base cases
  check(1, 0, 0, "zero floors");
  check(1, 1, 1, "one egg one floor");
  check(2, 1, 1, "multiple eggs one floor");

  // With one egg, every floor must potentially be tried
  check(1, 2, 2, "one egg two floors");
  check(1, 7, 7, "one egg seven floors");
  check(1, 20, 20, "one egg many floors");

  // Two eggs
  check(2, 2, 2, "two eggs two floors");
  check(2, 3, 2, "two eggs three floors");
  check(2, 6, 3, "two eggs six floors");
  check(2, 10, 4, "two eggs ten floors");
  check(2, 14, 5, "two eggs fourteen floors");

  // Three eggs
  check(3, 5, 3, "three eggs five floors");
  check(3, 14, 4, "three eggs fourteen floors");
  check(3, 25, 5, "three eggs twenty five floors");

  // More eggs
  check(4, 15, 4, "four eggs fifteen floors");
  check(5, 31, 5, "five eggs thirty one floors");

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}
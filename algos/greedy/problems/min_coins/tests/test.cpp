#include <bits/stdc++.h>

#include "../../../../../test_protocol.hpp"

using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(bool result, const char *input, int expected, int actual) {
  ++total;
  if (result)
    ++passed;
  dsa_test::emit_case(input, to_string(expected), to_string(actual), result);
}

int main() {
  check(minCoins(70, {1, 2, 5, 10, 20, 50}) == 2,
        R"({"amount":70,"coins":[1,2,5,10,20,50]})", 2,
        minCoins(70, {1, 2, 5, 10, 20, 50}));
  check(minCoins(3, {2, 4}) == -1, R"({"amount":3,"coins":[2,4]})", -1,
        minCoins(3, {2, 4}));
  check(minCoins(0, {1, 5}) == 0, R"({"amount":0,"coins":[1,5]})", 0,
        minCoins(0, {1, 5}));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

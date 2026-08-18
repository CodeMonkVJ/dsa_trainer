#include <bits/stdc++.h>

#include "../../../../../test_protocol.hpp"

using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(bool result, const char *input, double expected, double actual) {
  ++total;
  if (result)
    ++passed;
  dsa_test::emit_case(input, to_string(expected), to_string(actual), result);
}

int main() {
  check(abs(fractionalKnapsack({100, 60, 120}, {20, 10, 30}, 50) - 240.0) <
            1e-9,
        R"({"value":[100,60,120],"weight":[20,10,30],"capacity":50})", 240.0,
        fractionalKnapsack({100, 60, 120}, {20, 10, 30}, 50));
  check(abs(fractionalKnapsack({10, 20}, {5, 10}, 0)) < 1e-9,
        R"({"value":[10,20],"weight":[5,10],"capacity":0})", 0.0,
        fractionalKnapsack({10, 20}, {5, 10}, 0));
  check(abs(fractionalKnapsack({}, {}, 10)) < 1e-9,
        R"({"value":[],"weight":[],"capacity":10})", 0.0,
        fractionalKnapsack({}, {}, 10));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

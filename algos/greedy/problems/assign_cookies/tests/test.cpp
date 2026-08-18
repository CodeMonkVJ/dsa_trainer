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
  check(findContentChildren({1, 2, 3}, {1, 1}) == 1,
        R"({"children":[1,2,3],"cookies":[1,1]})", 1,
        findContentChildren({1, 2, 3}, {1, 1}));
  check(findContentChildren({1, 2}, {1, 2, 3}) == 2,
        R"({"children":[1,2],"cookies":[1,2,3]})", 2,
        findContentChildren({1, 2}, {1, 2, 3}));
  check(findContentChildren({}, {1}) == 0, R"({"children":[],"cookies":[1]})",
        0, findContentChildren({}, {1}));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

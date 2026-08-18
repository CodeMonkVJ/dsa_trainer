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
  check(
      minPlatforms({900, 940, 950, 1100, 1500, 1800},
                   {910, 1200, 1120, 1130, 1900, 2000}) == 3,
      R"({"arrival":[900,940,950,1100,1500,1800],"departure":[910,1200,1120,1130,1900,2000]})",
      3,
      minPlatforms({900, 940, 950, 1100, 1500, 1800},
                   {910, 1200, 1120, 1130, 1900, 2000}));
  check(minPlatforms({100, 200}, {100, 200}) == 1,
        R"({"arrival":[100,200],"departure":[100,200]})", 1,
        minPlatforms({100, 200}, {100, 200}));
  check(minPlatforms({}, {}) == 0, R"({"arrival":[],"departure":[]})", 0,
        minPlatforms({}, {}));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

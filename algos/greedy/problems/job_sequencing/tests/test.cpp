#include <bits/stdc++.h>

#include "../../../../../test_protocol.hpp"

using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

string pairJson(pair<int, int> value) {
  return "{\"jobs\":" + to_string(value.first) +
         ",\"profit\":" + to_string(value.second) + "}";
}

void check(bool result, const char *input, pair<int, int> expected,
           pair<int, int> actual) {
  ++total;
  if (result)
    ++passed;
  dsa_test::emit_case(input, pairJson(expected), pairJson(actual), result);
}

int main() {
  check(jobScheduling({2, 1, 2, 1, 3}, {100, 19, 27, 25, 15}) ==
            pair<int, int>{3, 142},
        R"({"deadline":[2,1,2,1,3],"profit":[100,19,27,25,15]})", {3, 142},
        jobScheduling({2, 1, 2, 1, 3}, {100, 19, 27, 25, 15}));
  check(jobScheduling({1, 1, 1}, {5, 6, 7}) == pair<int, int>{1, 7},
        R"({"deadline":[1,1,1],"profit":[5,6,7]})", {1, 7},
        jobScheduling({1, 1, 1}, {5, 6, 7}));
  check(jobScheduling({}, {}) == pair<int, int>{0, 0},
        R"({"deadline":[],"profit":[]})", {0, 0}, jobScheduling({}, {}));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

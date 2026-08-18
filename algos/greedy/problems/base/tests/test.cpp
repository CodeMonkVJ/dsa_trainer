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
  check(maxMeetings({1, 3, 0, 5, 8, 5}, {2, 4, 5, 7, 9, 9}) == 4,
        R"({"start":[1,3,0,5,8,5],"end":[2,4,5,7,9,9]})", 4,
        maxMeetings({1, 3, 0, 5, 8, 5}, {2, 4, 5, 7, 9, 9}));
  check(maxMeetings({1, 2, 3}, {1, 2, 3}) == 3,
        R"({"start":[1,2,3],"end":[1,2,3]})", 3,
        maxMeetings({1, 2, 3}, {1, 2, 3}));
  check(maxMeetings({}, {}) == 0, R"({"start":[],"end":[]})", 0,
        maxMeetings({}, {}));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

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
  check(maxMeetings({1}, {5}) == 1,
      R"({"start":[1],"end":[5]})", 1,
      maxMeetings({1}, {5}));
  check(maxMeetings({1, 2, 3}, {4, 5, 6}) == 1,
        R"({"start":[1,2,3],"end":[4,5,6]})", 1,
        maxMeetings({1, 2, 3}, {4, 5, 6}));
  
  check(maxMeetings({1, 2, 4}, {2, 4, 6}) == 3,
        R"({"start":[1,2,4],"end":[2,4,6]})", 3,
        maxMeetings({1, 2, 4}, {2, 4, 6}));
  
  check(maxMeetings({5, 1, 3}, {6, 2, 4}) == 3,
        R"({"start":[5,1,3],"end":[6,2,4]})", 3,
        maxMeetings({5, 1, 3}, {6, 2, 4}));
  
  check(maxMeetings({1, 4}, {5, 5}) == 1,
        R"({"start":[1,4],"end":[5,5]})", 1,
        maxMeetings({1, 4}, {5, 5}));
  
  check(maxMeetings({1, 4, 5}, {5, 5, 6}) == 2,
        R"({"start":[1,4,5],"end":[5,5,6]})", 2,
        maxMeetings({1, 4, 5}, {5, 5, 6}));
  
  check(maxMeetings({0, 1, 2, 3}, {10, 2, 3, 4}) == 3,
        R"({"start":[0,1,2,3],"end":[10,2,3,4]})", 3,
        maxMeetings({0, 1, 2, 3}, {10, 2, 3, 4}));
  
  check(maxMeetings({-5, -3, -1}, {-3, -1, 1}) == 3,
        R"({"start":[-5,-3,-1],"end":[-3,-1,1]})", 3,
        maxMeetings({-5, -3, -1}, {-3, -1, 1}));
  
  check(maxMeetings({1, 1, 1, 1}, {2, 3, 4, 5}) == 1,
        R"({"start":[1,1,1,1],"end":[2,3,4,5]})", 1,
        maxMeetings({1, 1, 1, 1}, {2, 3, 4, 5}));
  
  check(maxMeetings({1, 2, 2, 3}, {2, 2, 3, 4}) == 4,
        R"({"start":[1,2,2,3],"end":[2,2,3,4]})", 4,
        maxMeetings({1, 2, 2, 3}, {2, 2, 3, 4}));
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

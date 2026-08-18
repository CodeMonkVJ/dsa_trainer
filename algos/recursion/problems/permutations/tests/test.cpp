#include <bits/stdc++.h>
using namespace std;
#include "../../../../../test_protocol.hpp"

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(bool condition, const char *input, bool expected) {
  ++total;
  if (condition)
    ++passed;
  dsa_test::emit_case(input, expected ? "true" : "false",
                      condition ? "true" : "false", condition == expected);
}

set<vector<int>> asSet(vector<vector<int>> values) {
  return {values.begin(), values.end()};
}

int main() {
  check(asSet(permutations({1, 2, 3})) == asSet({{1, 2, 3},
                                                 {1, 3, 2},
                                                 {2, 1, 3},
                                                 {2, 3, 1},
                                                 {3, 1, 2},
                                                 {3, 2, 1}}),
        R"({"values":[1,2,3]})", true);
  check(asSet(permutations({1, 1, 2})) ==
            asSet({{1, 1, 2}, {1, 2, 1}, {2, 1, 1}}),
        R"({"values":[1,1,2]})", true);
  check(permutations({}).size() == 1 && permutations({})[0].empty(),
        R"({"values":[]})", true);
  check(asSet(permutations({-1, 0, -1})) ==
            asSet({{-1, -1, 0}, {-1, 0, -1}, {0, -1, -1}}),
        R"({"values":[-1,0,-1]})", true);
  check(permutations({7}).size() == 1 && permutations({7})[0] == vector<int>{7},
        R"({"values":[7]})", true);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}

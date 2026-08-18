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

int main() {
  check(ratInMaze({{1, 0, 0, 0}, {1, 1, 0, 1}, {1, 1, 0, 0}, {0, 1, 1, 1}}) ==
            vector<string>{"DDRDRR", "DRDDRR"},
        R"({"maze":[[1,0,0,0],[1,1,0,1],[1,1,0,0],[0,1,1,1]]})", true);
  check(ratInMaze({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}).size() == 12,
        R"({"maze":[[1,1,1],[1,1,1],[1,1,1]]})", true);
  check(ratInMaze({{1}}) == vector<string>{""}, R"({"maze":[[1]]})", true);
  check(ratInMaze({{0}}).empty(), R"({"maze":[[0]]})", true);
  check(ratInMaze({}).empty(), R"({"maze":[]})", true);
  check(ratInMaze({{1, 1}, {1}}).empty(), R"({"maze":[[1,1],[1]]})", true);
  check(ratInMaze({{1, 0}, {0, 1}}).empty(), R"({"maze":[[1,0],[0,1]]})", true);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
